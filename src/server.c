#include "server.h"

#define PORT    1432

static int sockfd;

bool server_init(void){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        log_writen("error creating a socket...");
        return false;
    }

    struct sockaddr_in serv_addr, client;

    bzero(&serv_addr, sizeof(struct sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&client, sizeof(serv_addr)) != 0){
        log_writen("failed to bind a socket...");
        return false;
    }

    if(listen(sockfd, SOMAXCONN) != 0){
        log_writen("failed to listen a socket");
        return false;
    }

    return true;
}

void server_listen(void){

    struct sockaddr_in client;

    unsigned int client_len = sizeof(client);

    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_len);
    if(connfd < 0){
        log_writen("client accept failed");
    }
}

void server_close(void){
    close(sockfd);
}