
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

struct ServerConfig {

  void autoconfig();
  void set_accept_handler(void(*)(char*, int));
  void set_message_handler(void(*)(char*, int));

  long num_accept_workers_;
  long num_msg_handle_workers_;
  long epoll_wait_timeout_;
  void(*accept_handler_)(char*, int);
  void(*message_handler_)(char*, int);

private:

  long num_cores();
  
};


void ServerConfig::autoconfig()
{
  num_accept_workers_ = 1;
  num_msg_handle_workers_ = num_cores() * 2;
  epoll_wait_timeout_ = 250;
}

void ServerConfig::set_accept_handler(void(*handler)(char*, int))
{
  accept_handler_ = handler;
}

void ServerConfig::set_message_handler(void(*handler)(char*, int))
{
  message_handler_ = handler;
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
  void set_message_handler(void(*handler)(char*, int));
  void reconfigure(ServerConfig&&);

private:
  template<typename Fn>
  int create_socket(const char* host, int port, Fn fn, int socket_flags = 0);
  int create_server_socket(const char* host, int port, int socket_flags);
  int bind_internal(const char* host, int port, int socket_flags);
  void accept_worker();
  void message_worker();
  bool listen_internal();

  std::thread* accept_worker_pool_;
  std::thread* msg_handle_worker_pool_;
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
  , epoll_fd_(-1)
  , is_running_(false)
  , shutdown_threads_(false)
{
  accept_worker_pool_ = new std::thread[config.num_accept_workers_];
  msg_handle_worker_pool_ = new std::thread[config.num_msg_handle_workers_];
}

Server::~Server()
{
  delete[] accept_worker_pool_;
  delete[] msg_handle_worker_pool_;
}

bool Server::listen(const char* host, int port, int socket_flags)
{
    if (bind_internal(host, port, socket_flags) < 0)
        return false;
    return listen_internal();
}

bool Server::is_running() const
{
    return is_running_;
}

void Server::stop()
{
    if (is_running_) {
        shutdown_threads_ = true;

        assert(svr_sock_ != -1);
        auto sock = svr_sock_;
        svr_sock_ = -1;
        shutdown(sock, SHUT_RDWR);
        close(sock);
    }
}

void Server::reconfigure(ServerConfig&& config)
{
  config = config;
}

template<typename Fn>
int Server::create_socket(const char* host, int port, Fn fn, int socket_flags)
{
    // Get address info
    struct addrinfo hints;
    struct addrinfo *result;

    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = socket_flags;
    hints.ai_protocol = 0;

    auto service = std::to_string(port);

    if (getaddrinfo(host, service.c_str(), &hints, &result)) {
        return -1;
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
       if (fn(sock, *rp)) {
          freeaddrinfo(result);
          return sock;
       }

       close(sock);
    }

    freeaddrinfo(result);
    return -1;
}

int Server::create_server_socket(const char* host, int port, int socket_flags)
{
    return create_socket(host, port,
        [](int sock, struct addrinfo& ai) -> bool {
            if (::bind(sock, ai.ai_addr, ai.ai_addrlen)) {
                  return false;
            }
            if (::listen(sock, 5)) { // Listen through 5 channels
                return false;
            }
            return true;
        }, socket_flags);
}

int Server::bind_internal(const char* host, int port, int socket_flags)
{
    svr_sock_ = create_server_socket(host, port, socket_flags);
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

void Server::accept_worker()
{
  char buffer[1024];

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
    config_.accept_handler_(buffer, new_connect_fd);  
  }
}

void Server::message_worker()
{
  epoll_event event;
  char buffer[1024];
  int written_index = 0;
  int read_index = 0;
  long packet_len;
  bool again = false;

  while (!shutdown_threads_)
  {
    //wait for fd to be readable
    if (!again)
    {
      int num_events = epoll_wait(epoll_fd_,
        &event,
        1,
        250);

      if (num_events > 0)
      {
        //did we read it all?
        int num_read = recv(event.data.fd, buffer, 1024, 0); //data cannot be longer than 1024
        
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
        if (num_read != -1)
        {
          
          config_.message_handler_(buffer, event.data.fd);
        }
      }
    }
    else
    {
      again = false;
      //add to packet
    }
  }
}

bool Server::listen_internal()
{
    auto ret = true;

    is_running_ = true;
    shutdown_threads_ = false;

    //create epoll system object
    epoll_fd_ = epoll_create1(0);
    
    ::listen(svr_sock_,
        10000);

    //kickoff threads
    for (int i = 0; i < config_.num_accept_workers_; ++i)
    {
      accept_worker_pool_[i] = std::thread(std::bind(&Server::accept_worker, this));
    }

    for (int i = 0; i < config_.num_msg_handle_workers_; ++i)
    {
      msg_handle_worker_pool_[i] = std::thread(std::bind(&Server::message_worker, this));
    }



    //wait for stop to be called
    for (int i = 0; i < config_.num_accept_workers_; ++i)
    {
        accept_worker_pool_[i].join();
    }

    for (int i = 0; i < config_.num_msg_handle_workers_; ++i)
    {
        msg_handle_worker_pool_[i].join();
    }

    //close epoll
    close(epoll_fd_);

    shutdown_threads_ = false;
    is_running_ = false;

    return ret;
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
  config.set_message_handler(message_handler);
  Server server(std::move(config));

  server.listen("localhost", 1234);
  
  return 0;
}