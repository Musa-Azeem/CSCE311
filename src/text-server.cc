/*
Written by Musa Azeem
text-server source
*/

#include "../headers/text-server.h"
#include <sys/sysinfo.h>    //using get_nproc_conf
#include <sys/socket.h>     //using socket
#include <unistd.h>         //using unlink, close
#include <iostream>


void TextServer::runServer() const{
    int sock_fd;        //unnamed socket file descriptor
    int client_req_sock_fd;     //client connection request for socket file descriptor

    // create socket
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0){
        std::cout << "Error creating socket" << std::endl;
        exit(-1);
    }

    // bind socket to address for server
    unlink(socket_path_.c_str()); //delete file if already exists
    int success = bind(sock_fd, 
                       reinterpret_cast<const sockaddr*>(&sock_addr_),
                       sizeof(sock_addr_));
    if(success<0){
        std::cout << "Error binding socket" << std::endl;
        exit(-1);
    }

    // Listen for client connections
    const size_t kMax_clients = get_nprocs_conf() - 1;
    success = listen(sock_fd, kMax_clients);
    if (success < 0){
        std::cout << "Error listening for client" << std::endl;
        exit(-1);
    }
}