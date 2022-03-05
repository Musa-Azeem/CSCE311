/*
Written by Musa Azeem
test server header
*/

#ifndef TEXTSERVER
#define TEXTSERVER
#include "../inc/Unix-Domain-Socket.h"

class TextServer: public UnixDomainSocket{
    public:
      using UnixDomainSocket::UnixDomainSocket;
      void runServer() const;
    private:
      const size_t kRead_buffer_size = 64;
};

#endif