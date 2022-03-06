/*
Written by Musa Azeem
text-server source
*/

#include "../inc/text-server.h"
#include "../inc/search.h"
#include <sys/sysinfo.h>    //using get_nproc_conf
#include <sys/socket.h>     //using socket
#include <unistd.h>         //using unlink, close
#include <iostream>
#include <vector>

void TextServer::runServer() const{
    int sock_fd;            //unnamed socket file descriptor
    int client_sock_fd;     //client connection request socket file descriptor
    const size_t kMax_clients = get_nprocs_conf() - 1;   //maximum number of clients
    char read_buffer[kRead_buffer_size];                //read buffer to read from client
    ssize_t bytes_read;             //record number of bytes read from client str
    ssize_t bytes_wrote;             //record number of bytes wrote to client
    Search s;                   //object to process data from client

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
    if(success < 0){
        std::cout << "Error listening for client" << std::endl;
        exit(-1);
    }
    while(true){
        // Accept connection from client
        client_sock_fd = accept(sock_fd, nullptr, nullptr);
        if(client_sock_fd < 0){
            std::cout << "Error accepting client connection" << std::endl;
            continue;
        }
        std::clog << "CLIENT CONNECTED" << std::endl;

        // Recieve data from client
        bytes_read = read(client_sock_fd, read_buffer, kRead_buffer_size);
        if(bytes_read > 0){
            // std::clog << "read: " << bytes_read << std::endl;
            s = Search(read_buffer);

            std::clog << "PATH: " << s.get_path() << std::endl;
            std::clog << "SEEKING: " << s.get_search_str() << std::endl;
        }
        else if(bytes_read < 0){
            std::cout << "Error reading client path string" << std::endl;
            continue;
        }

        //Search file for search string
        if(s.search()){
            std::string ret = "";
            for(auto line: s.get_found_lines()){
                ret += line + "\n";
            }
            bytes_wrote = write(client_sock_fd, &ret[0], ret.size()+1);
            if(bytes_wrote < 0){
                std::cout << "Error writing back" << std::endl;
                continue;
            }
            std::clog << "BYTES SENT: " << bytes_wrote << std::endl;
        }
        else{
            char inv[] = "INVALID FILE";
            bytes_wrote = write(client_sock_fd, inv, sizeof(inv));
            if(bytes_wrote < 0){
                std::cout << "Error writing back" << std::endl;
                continue;
            }
            std::clog << "BYTES SENT: " << bytes_wrote << std::endl;
        }
    }
}