/*
Written by Musa Azeem
text client source code
*/

#include "../inc/text-client.h"
#include <sys/sysinfo.h>    //using get_nproc_conf
#include <sys/socket.h>     //using socket
#include <unistd.h>         //using unlink, close
#include <iostream>

TextClient::TextClient(const char *socket_path, const char *path_str, const char *search_str)
    : UnixDomainSocket(socket_path)
{
    this->path_str = std::string(path_str);
    this->search_str = std::string(search_str);
}
void TextClient::print() const{
    std::cout << path_str << std::endl;
    std::cout << search_str << std::endl;
}
void TextClient::runClient() const{
    // open nameless Unix socket
    int sock_fd;
    // char write_buffer[kWrite_buffer_size];
    char read_buffer[kBuffer_size]; 

    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0){
        std::cout << "Error creating socket" << std::endl;
        exit(-1);
    }

    //connect to an existing socket
    int success = connect(sock_fd,
                          reinterpret_cast<const sockaddr*>(&sock_addr_),
                          sizeof(sock_addr_));
    if(success < 0){
        std::cout << "Error connecting to socket" << std::endl;
        exit(-1);
    }
    std::cout << "SERVER CONNECTION ACCEPTED" << std::endl;

    // write to socket
    ssize_t bytes_wrote_path = write(sock_fd, &path_str[0], path_str.size()+1);
    if(bytes_wrote_path < 0){
        std::cout << "Error writing to socket" << std::endl;
        exit(-1);
    }
    std::cout << "Send path" << path_str.size()+1 << std::endl;

    sleep(.1);
    
    ssize_t bytes_wrote_search = write(sock_fd, &search_str[0], search_str.size()+1);
    if(bytes_wrote_search < 0){
        std::cout << "Error writing to socket" << std::endl;
        exit(-1);
    }
    std::cout << "Send search" << search_str.size()+1 << std::endl;

    if(bytes_wrote_path == 0){
        std::cout << "Server dropped connection" << std::endl;
        exit(-2);
    }

    std::cout <<"waiting for writeback" << std::endl;

    success = read(sock_fd, read_buffer, kBuffer_size);
    if(success<0){
        std::cout << "Error reading" << std::endl;
    }
    std::cout << read_buffer << std::endl;
    // while(1){
    //     std::cin.getline(write_buffer, kWrite_buffer_size);
    //     while(std::cin.gcount() > 0){
    //         if(std::cin.gcount() == kWrite_buffer_size - 1 && std::cin.fail()){
    //             std::cin.clear();
    //         }
    //         ssize_t bytes_wrote = write(sock_fd, write_buffer, std::cin.gcount());
    //         std::cout << "Send " << std::cin.gcount() << std::endl;

    //         if(bytes_wrote < 0){
    //             std::cout << "Error writing to socket" << std::endl;
    //             exit(-1);
    //         }
    //         if(bytes_wrote == 0){
    //             std::cout << "Server dropped connection" << std::endl;
    //             exit(-2);
    //         }
    //         int n = read(sock_fd, read_buffer, 64);
    //         if(n<0){
    //             std::cout << "Error reading" << std::endl;
    //         }
    //         std::cout << read_buffer << std::endl;

    //         std::cin.getline(write_buffer, kWrite_buffer_size);
    //     }
    // }
}

