#include "shared.h"
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{

  int sock = create_socket();

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(1234);

  if (checkerrno(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)))
  {

    fprintf(stderr, "resolved host");
    if (checkerrno(connect(sock, (sockaddr*)&addr, sizeof(addr))))
    {

      fprintf(stderr, "connected to host");
      send(sock, "this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a \
      2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. this is a 2000 byte string. ", 11767, 0);
    }
    else
    {
      fprintf(stderr, "failed to connect to host");
    }
  }
  else
  {

    fprintf(stderr, "failed to resolve host");
  }

  return 0;
}