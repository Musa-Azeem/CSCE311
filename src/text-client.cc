/*
Written by Musa Azeem
text client source code
*/

#include "../inc/text-client.h"
#include <sys/sysinfo.h>    //using get_nproc_conf
#include <sys/socket.h>     //using socket
#include <unistd.h>         //using unlink, close
#include <sstream>          //using string stream
#include <iostream>

TextClient::TextClient(const char *socket_path, const char *path_str, const char *search_str)
    : UnixDomainSocket(socket_path)
{
    this->path_str = std::string(path_str);
    this->search_str = std::string(search_str);
}
void TextClient::print(){
    std::cout << path_str << std::endl;
    std::cout << search_str << std::endl;
}
void TextClient::runClient(){
    int sock_fd;
    // char read_buffer[kBuffer_size]; 
    ssize_t bytes_wrote;
    ssize_t bytes_read;

    // open nameless Unix socket
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
    std::string write_buffer = path_str + "\t" + search_str;
    bytes_wrote = write(sock_fd, &write_buffer[0], write_buffer.size()+1);
    if(bytes_wrote < 0){
        std::cout << "Error writing to socket" << std::endl;
        exit(-1);
    }
    // std::cout << "Sent " << write_buffer.size()+1 << std::endl;

    bytes_read = read(sock_fd, read_buffer, kBuffer_size);
    if(bytes_read < 0){
        std::cout << "Error reading back" << std::endl;
    }
    print_strings();
    std::clog << "BYTES RECIEVED: " << bytes_read << std::endl;
}

void TextClient::print_strings(){
    std::stringstream ss(read_buffer);
    std::string line;
    int i = 1;
    while(std::getline(ss, line)){
        std::clog << i << "\t" << line << std::endl;
        i += 1;
    }
}