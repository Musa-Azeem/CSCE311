/*
Written by Musa Azeem
Unix Domain Socket Class Header
*/

#ifndef UNIXDOMAINSOCKET
#define UNIXDOMAINSOCKET
#include <sys/un.h>         //using struct sockaddr_un
#include <string>

class UnixDomainSocket{
    public:
      explicit UnixDomainSocket(const char *socket_path);
    protected:
      ::sockaddr_un sock_addr_;
      std::string socket_path_;
};

#endif