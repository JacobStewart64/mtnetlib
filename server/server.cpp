
#include <thread>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <functional>
#include <memory.h>
#include <signal.h>
#include <mutex>

typedef void(*lpfn)(char*, int);

class ServerConfig {
public:
  ServerConfig();
  ~ServerConfig();
  void autoconfig();
  void set_accept_handler(lpfn);
  void set_message_handler(lpfn);
  void set_num_accept_workers(long);
  void set_num_msg_handle_workers(long);
  void set_backlog(long);
  lpfn get_accept_handler();
  lpfn get_message_handler();
  long get_num_accept_workers();
  long get_num_msg_handle_workers();
  long get_backlog();
  bool good();

private:
  long num_cores();

  long num_accept_workers_;
  long num_msg_handle_workers_;
  long backlog_;
  lpfn accept_handler_;
  lpfn message_handler_;
  
};

ServerConfig::ServerConfig() {}

ServerConfig::~ServerConfig() {}

void ServerConfig::autoconfig()
{
  num_accept_workers_ = 1;
  num_msg_handle_workers_ = num_cores() * 2;
  backlog_ = 10000;
}

void ServerConfig::set_accept_handler(void(*handler)(char*, int))
{
  accept_handler_ = handler;
}

void ServerConfig::set_message_handler(void(*handler)(char*, int))
{
  message_handler_ = handler;
}

void ServerConfig::set_num_accept_workers(long n)
{
  num_accept_workers_ = n;
}

void ServerConfig::set_num_msg_handle_workers(long n)
{
  num_msg_handle_workers_ = n;
}

void ServerConfig::set_backlog(long backlog)
{
  backlog_ = backlog;
}

lpfn ServerConfig::get_accept_handler()
{
  return accept_handler_;
}

lpfn ServerConfig::get_message_handler()
{
  return message_handler_;
}

long ServerConfig::get_num_accept_workers()
{
  return num_accept_workers_;
}

long ServerConfig::get_num_msg_handle_workers()
{
  return num_msg_handle_workers_;
}

long ServerConfig::get_backlog()
{
  return backlog_;
}

//assert data is good to use
//compiles out in release?
bool ServerConfig::good()
{
  assert(backlog_ >= 0);
  assert(num_accept_workers_ > 0);
  assert(num_msg_handle_workers_ > 0);
  assert(accept_handler_ != nullptr);
  assert(message_handler_ != nullptr);
}

long ServerConfig::num_cores()
{
  long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  return nprocs;
}


class Server {

public:
  Server(ServerConfig&& config);
  ~Server();
  bool listen(const char* host, int port, int socket_flags = 0);
  bool is_running() const;
  void stop();
  void reconfigure(ServerConfig&&);

private:
  void create_socket(const char* host, int port, int socket_flags = 0);
  int bind_internal(const char* host, int port, int socket_flags);
  template<long _fixed_buffer_size = 1024>
  void accept_worker();
  template<long _fixed_buffer_size = 1024>
  void message_worker(bool&, std::mutex*);
  void launch_threads();
  void join_threads();
  void listen_internal();

  std::thread* accept_worker_pool_;
  std::thread* msg_handle_worker_pool_;
  std::mutex** per_msg_handle_worker_mutex_;
  bool* msg_handle_worker_running_flags_;
  ServerConfig config_;
  int svr_sock_;
  int epoll_fd_;
  bool is_running_;
  bool shutdown_threads_;
};

Server::Server(ServerConfig&& config)
  : accept_worker_pool_(nullptr)
  , msg_handle_worker_pool_(nullptr)
  , config_(std::move(config))
  , svr_sock_(-1)
  , epoll_fd_(epoll_create1(0))
  , is_running_(false)
  , shutdown_threads_(false)
{
  config_.good();
}

Server::~Server()
{

}

bool Server::listen(const char* host, int port, int socket_flags)
{
    if (bind_internal(host, port, socket_flags) < 0)
        return false;
    listen_internal();
    return true;
}

bool Server::is_running() const
{
    return is_running_;
}

void Server::stop()
{
    if (is_running_) {
      assert(svr_sock_ != -1);
      
      //we are not running at all now
      is_running_ = false;

      //threads will start closing after
      //they finish their iteration
      shutdown_threads_ = true;
      
      //unblock all of our accept calls
      shutdown(svr_sock_, SHUT_RDWR);
      close(svr_sock_);

      //svr_sock_ back in init state
      svr_sock_ = -1;

      //wait for threads to exit and join
      join_threads();
    }
}

void Server::reconfigure(ServerConfig&& config)
{
  config = config;
}

void Server::create_socket(const char* host, int port, int socket_flags)
{
    // Get address info
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = socket_flags;
    hints.ai_protocol = 0;

    //replace with c
    auto service = std::to_string(port);

    if (getaddrinfo(host, service.c_str(), &hints, &result)) {
      svr_sock_ = -1;
      return;
    }

    for (auto rp = result; rp; rp = rp->ai_next) {
       // Create a socket
       auto sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
       if (sock == -1) {
          continue;
       }

       // Make 'reuse address' option available
       int yes = 1;
       setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));

       // bind or connect
       yes = ::bind(sock, (const sockaddr*)rp, rp->ai_addrlen);
       if (yes != -1)
       {
         yes = ::listen(sock, config_.get_backlog());
         if (yes != -1)
         {
           svr_sock_ = sock;
           return;
         }
       }

       close(sock);
    }

    freeaddrinfo(result);
    svr_sock_ = -1;
}

int Server::bind_internal(const char* host, int port, int socket_flags)
{
    create_socket(host, port, socket_flags);
    if (svr_sock_ == -1) {
        return -1;
    }

    if (port == 0) {
        struct sockaddr_storage address;
        socklen_t len = sizeof(address);
        if (getsockname(svr_sock_, reinterpret_cast<struct sockaddr *>(&address), &len) == -1) {
            return -1;
        }
        if (address.ss_family == AF_INET) {
          return ntohs(reinterpret_cast<struct sockaddr_in*>(&address)->sin_port);
        } else if (address.ss_family == AF_INET6) {
          return ntohs(reinterpret_cast<struct sockaddr_in6*>(&address)->sin6_port);
        } else {
          return -1;
        }
    } else {
        return port;
    }
}

template<const long _fixed_buffer_size>
void Server::accept_worker()
{
  char buffer[_fixed_buffer_size];

  while (!shutdown_threads_)
  {
    int new_connect_fd = accept(svr_sock_,
      0, //&addr_in
      0);//&addrlen

    epoll_event event;
    event.events = EPOLLIN | EPOLLONESHOT;
    event.data.fd = new_connect_fd;

    epoll_ctl(epoll_fd_,
      EPOLL_CTL_ADD,
      new_connect_fd,
      &event);

    //let them have an event on connect
    config_.get_accept_handler()(buffer, new_connect_fd);  
  }
}

template<const long _fixed_buffer_size>
void Server::message_worker(bool& im_running, std::mutex* my_mutex)
{
  my_mutex->lock();
  im_running = true;
  my_mutex->unlock();

  epoll_event event;
  char buffer[_fixed_buffer_size];
  long packet_len;
  bool again = false;

  while (!shutdown_threads_)
  {
    //mock - does not work - will maintain global
    //map of pair<'packet', worker-switch-flag> (static buffer with nice interface,
    //worker-switch-flag for identifying if need more read)
    //to fd. fd : pair<'packet', worker-switch-flag>
    if (!again)
    {
      //wait for fd to be readable
      int num_events = epoll_wait(epoll_fd_,
        &event,
        1,
        -1);

      if (num_events > 0)
      {
        //did we read it all?
        int num_read = recv(event.data.fd, buffer, _fixed_buffer_size, 0); //data cannot be longer than 1024
        
        //first 8 bytes of any buffer are packet length
        packet_len = (long)*buffer;
        if (num_read < packet_len && num_read != -1)
        {
          again = true; //read again on this fd into this packet
        }
        
        //pass a partial or a complete packet to message_handler_
        //partial packets will block when their data is consumed
        //and there is none left. You can work on your data
        //in a stream way and only consume what is needed
        //to get a head start and not wait for all data to arrive
        /*
            Here is a typical example: thread 1 is waiting for a condition, which may be fulfilled by thread 2.

            We use one mutex and one condition.

            pthread_mutex_t mutex;
            pthread_cond_t condition;

            thread 1 :

            pthread_mutex_lock(&mutex); //mutex lock
            while(!condition){
                pthread_cond_wait(&condition, &mutex); //wait for the condition
            }

            /* do what you want */

            /*pthread_mutex_unlock(&mutex);

            thread 2:

            pthread_mutex_lock(&mutex);

            /* do something that may fulfill the condition */

            //pthread_mutex_unlock(&mutex);
            //pthread_cond_signal(&condition); //wake up thread 1

        if (num_read != -1)
        {
          config_.get_message_handler()(buffer, event.data.fd);
        }
      }
    }
    else
    {
      again = false;
      //add to packet
    }
  }

  my_mutex->lock();
  im_running = false;
  my_mutex->unlock();
}

void Server::launch_threads()
{
  accept_worker_pool_ = new std::thread[config_.get_num_accept_workers()];
  msg_handle_worker_pool_ = new std::thread[config_.get_num_msg_handle_workers()];
  msg_handle_worker_running_flags_ = new bool[config_.get_num_msg_handle_workers()];
  per_msg_handle_worker_mutex_ = new std::mutex*[config_.get_num_msg_handle_workers()];

  for (int i = 0; i < config_.get_num_accept_workers(); ++i)
  {
    accept_worker_pool_[i] = std::thread(std::bind(&Server::accept_worker<1024>, this));
  }

  for (int i = 0; i < config_.get_num_msg_handle_workers(); ++i)
  {
    per_msg_handle_worker_mutex_[i] = new std::mutex();
    msg_handle_worker_running_flags_[i] = false;
    msg_handle_worker_pool_[i] = std::thread(std::bind(&Server::message_worker<1024>,
      this,
      msg_handle_worker_running_flags_[i],
      per_msg_handle_worker_mutex_[i]));
  }
}

void Server::join_threads()
{
  for (int i = 0; i < config_.get_num_accept_workers(); ++i)
  {
      accept_worker_pool_[i].join();
  }
  
  bool retry = true;
  while (retry)
  {
    retry = false;
    for (int i = 0; i < config_.get_num_msg_handle_workers(); ++i)
    {
      per_msg_handle_worker_mutex_[i]->lock();
      if (msg_handle_worker_running_flags_[i])
      {
        pthread_kill(msg_handle_worker_pool_[i].native_handle(), SIGCONT);
        retry = true;
      }
      per_msg_handle_worker_mutex_[i]->unlock();
    }
  }

  for (int i = 0; i < config_.get_num_msg_handle_workers(); ++i)
  {
      msg_handle_worker_pool_[i].join();
      delete per_msg_handle_worker_mutex_[i];
  }

  delete[] per_msg_handle_worker_mutex_;
  delete[] accept_worker_pool_;
  delete[] msg_handle_worker_pool_;
}

void Server::listen_internal()
{
    is_running_ = true;
    shutdown_threads_ = false;

    launch_threads();
}

void accept_handler(char* msg, int fd)
{
  //need to handle accept event?
}

void message_handler(char* msg, int fd)
{
  //need to handle recv?
}

int main()
{
  ServerConfig config;
  config.autoconfig();
  config.set_accept_handler(accept_handler);
  config.set_message_handler(message_handler);
  Server server(std::move(config));

  server.listen("localhost", 1234);

  usleep(1000000);

  server.stop();

  server.listen("localhost", 1234);

  usleep(1000000);

  server.stop();
  
  return 0;
}