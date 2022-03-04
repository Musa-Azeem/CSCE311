/*
Written by Musa Azeem
test server header
*/

#ifndef TEXTSERVER
#define TEXTSERVER
#include "../headers/Unix-Domain-Socket.h"

class TextServer: public UnixDomainSocket{
    public:
      using UnixDomainSocket::UnixDomainSocket;
      void runServer() const;
};

#endif