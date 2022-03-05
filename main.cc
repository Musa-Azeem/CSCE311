/*
Written by Musa Azeem
Main Method to run client and server
*/
#include "inc/Unix-Domain-Socket.h"
#include "inc/text-server.h"
#include "inc/text-client.h"

const char kSocket_path[] = "socket_cli_srv_domain_socket";
int main(int argc, char **argv){
    if (argc != 2){
        return 1;
    }

    if(strcmp(argv[1], "server") == 0){
        TextServer dss(kSocket_path);
        dss.runServer();
    }
    else if(strcmp(argv[1], "client") == 0){
        TextClient dsc(kSocket_path, "path", "search");
        dsc.runClient();
    }
    return 0;
}