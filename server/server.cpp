
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
#include <fstream>

class Server {

public:
  Server();
  bool listen(const char* host, int port, int socket_flags = 0);
  bool is_running() const;
  void stop();
  void set_message_handler(void(*handler)(char*, int));

private:
  template<typename Fn>
  int create_socket(const char* host, int port, Fn fn, int socket_flags = 0);
  int create_server_socket(const char* host, int port, int socket_flags);
  int bind_internal(const char* host, int port, int socket_flags);
  void worker();
  long num_cores();
  bool listen_internal();

  void(*message_handler_)(char*, int);
  std::thread* thread_pool_;
  int svr_sock_;
  int epoll_fd_;
  int n_cores_;
  bool is_running_;
  bool shutdown_threads_;

};

Server::Server()
  : message_handler_(nullptr)
  ,thread_pool_(nullptr)
  , svr_sock_(-1)
  , epoll_fd_(-1)
  , n_cores_(-1)
  , is_running_(false)
  , shutdown_threads_(false)
{
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

void Server::set_message_handler(void(*handler)(char*, int))
{
  message_handler_ = handler;
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

void Server::worker()
{
  epoll_event event;
  char buffer[1024];

  while (true)
  {
    //wait for fd to be readable
    int num_events = epoll_wait(epoll_fd_,
      &event,
      1,
      250);

    if (shutdown_threads_)
    {
      return;
    }

    if (num_events > 0)
    {
      if (event.data.fd == svr_sock_)
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

        epoll_event new_event;
        new_event.events = EPOLLIN | EPOLLONESHOT;
        new_event.data.fd = svr_sock_;

        epoll_ctl(epoll_fd_,
          EPOLL_CTL_MOD,
          svr_sock_,
          &new_event);
      }
      else
      { 
        int num_read = recv(event.data.fd, buffer, 1024, 0); //data cannot be longer than 1024
        if (num_read != -1)
        {
          message_handler_(buffer, event.data.fd);
        }
      }
    }
  }
}

long Server::num_cores()
{

  long nprocs = -1;
  nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  return nprocs;
}

bool Server::listen_internal()
{
    auto ret = true;

    is_running_ = true;
    shutdown_threads_ = false;

    //get number of cores * 2
    n_cores_ = num_cores() * 2;

    //create epoll system object
    epoll_fd_ = epoll_create1(0);
    
    //set listen_socket to look for
    //opportunity to accept
    epoll_event event;
    event.events = EPOLLIN | EPOLLONESHOT;
    event.data.fd = svr_sock_;

    epoll_ctl(epoll_fd_,
      EPOLL_CTL_ADD,
      svr_sock_,
      &event);
    

    ::listen(svr_sock_,
        10000);

    thread_pool_ = new std::thread[n_cores_];

    //kickoff threads
    for (int i = 0; i < n_cores_; ++i)
    {
        thread_pool_[i] = std::thread(std::bind(&Server::worker, this));
    }

    //wait for threads to be signalled to exit
    for (int i = 0; i < n_cores_; ++i)
    {
        thread_pool_[i].join();
    }

    delete[] thread_pool_;

    //close epoll
    close(epoll_fd_);

    shutdown_threads_ = false;
    is_running_ = false;

    return ret;
}


void message_handler(char* msg, int fd)
{
  char account_name[16];
  char account_password[16];

  int i = 0;
  for (;msg[i] != ':'; ++i)
    account_name[i] = msg[i];
  account_name[i] = '\0';

  ++i;
  int offset = i;
  for (;msg[i] != ':'; ++i)
    account_password[i - offset] = msg[i];
  account_password[i - offset] = '\0';

  //open the account file
  char filepath[256];
  sprintf(filepath, "../../accountdb/%s", account_name);
  std::ifstream account_file(filepath);
  
  char actual_password[16];
  memset(actual_password, 0, 16);
  if (!account_file.fail())
  {
    account_file >> actual_password;
  }

  if (strcmp(account_password, actual_password) == 0)
  {
    msg = "!";
    send(fd, msg, 1, 0);
  }
  else
  {
    msg = "?";
    send(fd, msg, 1, 0);
  }

  close(fd);
}

int main()
{
  Server server;
  server.set_message_handler(message_handler);

  server.listen("localhost", 1234);
  
  return 0;
}