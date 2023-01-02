#include "server.h"

bool socket_init(void){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        write_logn("error creating a socket...");
        return false;
    }

    

    return true;
}