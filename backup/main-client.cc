/*
Written by Musa Azeem
Main method for text client
*/

#include "inc/text-client.h"
#include <iostream>

int main(int argv, char **argc){
    if(argv != 4){
        std::cout << "usage: ./text-server domain_socket_file_name file_path search_string" << std::endl;
        return 1;
    }
    TextClient client(argc[1], argc[2], argc[3]);
    client.runClient();
    return 0;
}