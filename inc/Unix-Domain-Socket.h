/*
Written by Musa Azeem
Unix Domain Socket Class Header
This file defines a class UnixDomainSocket, 
  which acts as base class for the text-server and text-client classes
Class variables: 
  socker_addr:  struct containing type and address of socket
  socket_path_: path to socket file
*/

#ifndef UNIXDOMAINSOCKET
#define UNIXDOMAINSOCKET
#include <sys/un.h>         //using struct sockaddr_un
#include <string>

class UnixDomainSocket{
  public:
    explicit UnixDomainSocket(const char *socket_path); //constructor
  protected:
    ::sockaddr_un sock_addr_;
    std::string socket_path_;   
};

#endif