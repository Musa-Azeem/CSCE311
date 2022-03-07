/*
Written by Musa Azeem
TextServer Class header
This file defines a class TextServer, to which clients can connect to through a Unix Domain Socket
Class Variables:
  kRead_buffer_size:  Maximum number of bytes Server can read from a Client
Class Functions:
  Constructor:  uses base class constructor
  runServer:    starts socket server
*/

#ifndef TEXTSERVER
#define TEXTSERVER
#include "../inc/Unix-Domain-Socket.h"

class TextServer: public UnixDomainSocket{
    public:
      using UnixDomainSocket::UnixDomainSocket;
      void runServer() const;
    private:
      const size_t kRead_buffer_size = 1024;
};

#endif