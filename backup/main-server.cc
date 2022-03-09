/*
Written by Musa Azeem
Main method for text server
*/

#include "inc/text-server.h"
#include <iostream>

int main(int argv, char **argc){
    if(argv != 2){
        std::cout << "usage: ./text-server domain_socket_file_name" << std::endl;
        return 1;
    }
    TextServer server(argc[1]);
    server.runServer();
    return 0;
}