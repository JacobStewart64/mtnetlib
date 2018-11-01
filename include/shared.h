#pragma once

#include <unistd.h>
#include <sys/socket.h>


int create_socket()
{

  int sock = socket(AF_INET,
    SOCK_STREAM,
    0);

  return sock;
}