/*
Written by Musa Azeem
text client header
*/

#ifndef TEXTCLIENT
#define TEXTCLIENT
#include "../inc/Unix-Domain-Socket.h"

class TextClient: public UnixDomainSocket{
    public:
      using UnixDomainSocket::UnixDomainSocket;
      void runClient() const;
};

#endif