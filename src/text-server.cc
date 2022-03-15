/*
Written by Musa Azeem
TextServer Class source code
This file defines the functions for TextServer class
Functions:
    runServer: 
        Creates and binds socket to server
        continuosly listens and waits for client connections
        when client connects, server waits to recieve a string containing path to file and string to search for
        server creates Search object with data from client
        server recieves found lines from Search object, and sends them to client
        prints number of bytes sent to client to stdlog
        server does not terminate, it continues to listen for new client connections
*/

#include "../inc/text-server.h"
#include "../inc/search.h"  //using Search
#include <sys/sysinfo.h>    //using get_nproc_conf
#include <sys/socket.h>     //using socket
#include <unistd.h>         //using unlink
#include <iostream>
#include <vector>

void TextServer::runServer() const{
    int sock_fd;            //unnamed socket file descriptor
    int client_sock_fd;     //client connection socket file descriptor
    const size_t kMax_clients = get_nprocs_conf() - 1;   //maximum number of clients based on number of machine's execution contexts
    char read_buffer[kRead_buffer_size];                 //read buffer to read from client
    ssize_t bytes_read;     //record number of bytes read from client str
    ssize_t bytes_wrote;    //record number of bytes wrote to client
    Search s;               //object to process data from client
    // const std::string kill_msg = "VERY VERY DISTINCT KILL MESSAGE (ITS SO DISTINCT)";
    const std::string kill_msg = "\004";

    // create socket
    sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sock_fd < 0){
        std::cerr << "Error creating socket" << std::endl;
        exit(-1);
    }

    // bind socket to address for server
    unlink(socket_path_.c_str()); //delete file if already exists
    int success = bind(sock_fd, 
                       reinterpret_cast<const sockaddr*>(&sock_addr_),
                       sizeof(sock_addr_));
    if(success<0){
        std::cerr << "Error binding socket" << std::endl;
        exit(-1);
    }

    std::clog << "SERVER STARTED" << std::endl;
    std::clog << "\tMAX CLIENTS: " << kMax_clients << std::endl;

    // Listen for client connections
    success = listen(sock_fd, kMax_clients);
    if(success < 0){
        std::cerr << "Error listening for client" << std::endl;
        exit(-1);
    }
    while(true){
        // Accept connection from client
        client_sock_fd = accept(sock_fd, nullptr, nullptr);
        if(client_sock_fd < 0){
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }
        std::clog << "CLIENT CONNECTED" << std::endl;

        // Recieve data from client
        bytes_read = read(client_sock_fd, read_buffer, kRead_buffer_size);
        if(bytes_read < 0){
            std::cerr << "Error reading client path string" << std::endl;
            continue;
        }
        s = Search(read_buffer);
        std::clog << "PATH: \"" << s.get_path() << "\"" << std::endl;
        std::clog << "SEEKING: \"" << s.get_search_str() << "\"" << std::endl;

        //Search file for search string and send found lines to client
        success = s.search();
        if(success){
            std::string ret = "";
            for(auto line: s.get_found_lines()){
                //send one string of data, delimited by newline characters
                ret += line + "\n";
            }
            ret += kill_msg;    // append kill message to end of lines
            bytes_wrote = write(client_sock_fd, &ret[0], ret.size()+1);
            if(bytes_wrote < 0){
                std::cerr << "Error writing back" << std::endl;
                continue;
            }
            bytes_wrote -= kill_msg.size();
            std::clog << "BYTES SENT: " << bytes_wrote << std::endl;
        }
        else{
            std::string inv = "INVALID FILE" + kill_msg;
            bytes_wrote = write(client_sock_fd, &inv[0], inv.size()+1);
            if(bytes_wrote < 0){
                std::cerr << "Error writing back" << std::endl;
                continue;
            }
            bytes_wrote -= kill_msg.size();
            std::clog << "BYTES SENT: " << bytes_wrote << std::endl;
        }
    }
}