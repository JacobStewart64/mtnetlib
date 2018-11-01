#include <cstdlib>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>


bool checkerrno(int fd,
  const char* file,
  int line)
{
  
  if(fd == -1)
  {

    char command[10];
    sprintf(command,
      "errno %d",
      errno);

    fprintf(stderr,
      "%s:%d\n",
      file,
      line);

    std::system(command);
    return false;
  }

  return true;
}


#define checkerrno(x) checkerrno(x, __FILE__, __LINE__)


long num_cores()
{

  long nprocs = -1;
  nprocs = sysconf(_SC_NPROCESSORS_ONLN);
  checkerrno(nprocs);
  return nprocs;
}


int create_socket()
{

  int sock = socket(AF_INET,
    SOCK_STREAM,
    0);

  if (checkerrno(sock))
  {
    fprintf(stderr,
      "created socket %d\n",
      sock);
    return sock;
  }

  fprintf(stderr,
    "failed to create socket\n");
  return -1;
}