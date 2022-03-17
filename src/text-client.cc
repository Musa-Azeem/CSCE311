/*
Written by Musa Azeem
TextClient Class source code
This function defines the functions of TextClient class
Functions:
    Constructor:
        uses base class constructor to initialize inherited variables
        initializes path_str with given path string
        initializes search_str with given search string
    runClient:
        creates and connects socket to server
        writes path_str and search_str to server, delimited by tab character
        reads back the found lines sent by server
        calls print_strings to print found lines
        prints number of bytes recieved from server to stdlog
    print_strings:
        prints found lines to stdout
        formats by adding line number and tab before each found line
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
void TextClient::runClient(){
    int sock_fd;            //unnamed socket file descriptor
    ssize_t bytes_wrote;    //record number of bytes wrote to server
    ssize_t bytes_read;     //record number of bytes read from server
    char read_buffer[kRead_buffer_size];
    // const std::string kill_msg = "VERY VERY DISTINCT KILL MESSAGE (ITS SO DISTINCT)";
    const std::string kill_msg = "\004";

    // open nameless Unix socket
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0){
        std::cerr << "Error creating socket" << std::endl;
        exit(-1);
    }

    //connect to an existing socket
    int success = connect(sock_fd,
                          reinterpret_cast<const sockaddr*>(&sock_addr_),
                          sizeof(sock_addr_));
    if(success < 0){
        std::cerr << "Error connecting to socket" << std::endl;
        exit(-1);
    }
    std::clog << "SERVER CONNECTION ACCEPTED" << std::endl;

    // write to socket - delimit path and search strings by tab character
    std::string write_buffer = path_str + "\t" + search_str;
    bytes_wrote = write(sock_fd, &write_buffer[0], write_buffer.size()+1);
    if(bytes_wrote < 0){
        std::cerr << "Error writing to socket" << std::endl;
        exit(-1);
    }
    bytes_read = 0;
    int i = 0;
    while(true){
        success = read(sock_fd, read_buffer, kRead_buffer_size);
        if(success < 0){
            std::cerr << "Error reading back" << std::endl;
        }
        found_lines += read_buffer;
        bytes_read += success;
        ssize_t pos = found_lines.find(kill_msg);
        if(pos != std::string::npos){
            found_lines.erase(pos, kill_msg.size());
            found_lines += "\n";
            bytes_read -= kill_msg.size();
            break;
        }
        i+=1;
    }
    print_strings();
    std::clog << "BYTES RECIEVED: " << bytes_read << std::endl;
}

void TextClient::print_strings(){
    std::stringstream ss(found_lines);
    std::string line;
    int i = 1;
    while(std::getline(ss, line)){
        std::cout << i << "\t" << line << std::endl;
        i += 1;
    }
}