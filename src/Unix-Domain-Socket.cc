/*
Written by Musa Azeem
Unix Domain Socket Source
*/

#include "../inc/Unix-Domain-Socket.h"
#include <sys/socket.h>     //using socket
#include <sys/un.h>         //using struct sockaddr_un
#include <cstring>          //using strncpy, strerror
#include <string>

UnixDomainSocket::UnixDomainSocket(const char *socket_path){
    socket_path_ = std::string(socket_path);
    sock_addr_ = {};
    sock_addr_.sun_family = AF_UNIX;    //UNIX domain socket
    strncpy(sock_addr_.sun_path + 1, socket_path, sizeof(sock_addr_.sun_path) - 2);
}