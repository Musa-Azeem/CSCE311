/*
Written by Musa Azeem
text client header
*/

#ifndef TEXTCLIENT
#define TEXTCLIENT
#include "../headers/Unix-Domain-Socket.h"

class TextClient: public UnixDomainSocket{
    public:
      using UnixDomainSocket::UnixDomainSocket;
      void runClient() const;
};

#endif