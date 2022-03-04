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
    const size_t kMax_clients = get_nprocs_conf() - 1;
    const size_t kRead_buffer_size = 64;

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

    std::clog << "SERVER STARTED" << std::endl;
    std::clog << "\tMAX CLIENTS: " << kMax_clients << std::endl;

    // Listen for client connections
    success = listen(sock_fd, kMax_clients);
    if (success < 0){
        std::cout << "Error listening for client" << std::endl;
        exit(-1);
    }

    char read_buffer[kRead_buffer_size];
    int bytes_read;
    while(1){
        // Accept connection from client
        client_req_sock_fd = accept(sock_fd, nullptr, nullptr);
        if(client_req_sock_fd < 0){
            std::cout << "Error accepting client connection" << std::endl;
            continue;
        }
        std::clog << "CLIENT CONNECTED" << std::endl;

        // Recieve data from client(s)
        bytes_read = read(client_req_sock_fd, read_buffer, kRead_buffer_size);
        const char kKil_msg[] = "exit";

        while(bytes_read > 0){
            if(strcmp(read_buffer, kKil_msg)==0){
                std::clog << "Shutting down Server" << std::endl;

                bytes_read = 0; 
                break;
            }
            std::clog << "read: " << bytes_read << std::endl;
            std::clog << read_buffer << std::endl;

            //process file to get return string
            // char word[] = "recieved";
            // write(sock_fd, word, sizeof(word));

            bytes_read = read(client_req_sock_fd, read_buffer, kRead_buffer_size);
        }

        if (bytes_read == 0){
            std::clog << "CLIENT DISCONNECTED" << std::endl;
            close(client_req_sock_fd);
        }
        else if(bytes_read < 0){
            std::cout << "Error reading client buffer" << std::endl;
            exit(-1);
        }
    }
}