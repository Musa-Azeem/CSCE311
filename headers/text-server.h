/*
Written by Musa Azeem
test server header
*/

#ifndef TEXTSERVER
#define TEXTSERVER
#include "headers/Unix-Domain-Socket.h"
#include <sys/socket.h>     //using socket
#include <sys/un.h>         //using struct sockaddr_un

class TextServer: public UnixDomainSocket{
    public:
      using UnixDomainSocket::UnixDomainSocket;
      void runServer() const;
};

#endif