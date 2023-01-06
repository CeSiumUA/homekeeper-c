#include "server.h"

#ifdef __STDC_NO_THREADS__
#error Threads are not supported by compiler
#endif

typedef struct client_handler {
    thrd_t thread;
    int socket_descriptor;
    struct sockaddr_in *client;
    struct client_handler *next;
} client_handler;

#define PORT            1432
#define RX_BUFF_SIZE    2048

static int sockfd;
static bool is_server_active = true;
static thrd_t listening_thread;
static client_handler *client_handlers = NULL;

static int accept_connections(void *arg);
static client_handler * add_client_handler(int descriptor, struct sockaddr_in *client);
static int process_connection(void *arg);
static void remove_client_handler(client_handler *handler);

bool server_init(void){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        log_writen("error creating a socket...");
        return false;
    }

    struct sockaddr_in serv_addr;

    bzero(&serv_addr, sizeof(struct sockaddr_in));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) != 0){
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
    thrd_create(&listening_thread, accept_connections, NULL);
    thrd_detach(listening_thread);
}

void server_close(void){
    is_server_active = false;
    close(sockfd);
    while(client_handlers != NULL){
        client_handler *next = client_handlers->next;
        free(client_handlers->client);
        free(client_handlers);
        client_handlers = next;
    }
}

static int accept_connections(void *arg){
    while(is_server_active){
        struct sockaddr_in *client = malloc(sizeof(struct sockaddr_in));
        
        unsigned int client_len = sizeof(client);

        int connfd = accept(sockfd, (struct sockaddr*)client, &client_len);
        client_handler *handler = add_client_handler(connfd, client);
        if(connfd < 0){
            log_writen("client accept failed");
            continue;
        }
        thrd_create(&handler->thread, process_connection, handler);
        thrd_detach(handler->thread);
    }

    return 0;
}

static client_handler * add_client_handler(int descriptor, struct sockaddr_in *client){
    client_handler *handler = malloc(sizeof(client_handler));

    handler->socket_descriptor = descriptor;
    handler->client = client;

    if(client_handlers == NULL){
        client_handlers = handler;
    }
    else{
        client_handler *handle = client_handlers;

        while(handle->next != NULL){
            handle = handle->next;
        }

        handle->next = handler;
    }

    return handler;
}

static void remove_client_handler(client_handler *handler){
    client_handler *previous_handler = client_handlers;
    if(previous_handler == handler){
        client_handlers = handler->next;
        free(handler->client);
        free(handler);
        return;
    }

    while(previous_handler->next != handler){
        previous_handler = previous_handler->next;
    }

    previous_handler->next = handler->next;
    free(handler);
}

static int process_connection(void *arg){
    client_handler *handle = (client_handler *)arg;

    char addr[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(handle->client->sin_addr), addr, INET_ADDRSTRLEN);

    log_writen("handling client connection: from address %s and port %d", addr, handle->client->sin_port);

    uint8_t buff[RX_BUFF_SIZE];
    while(1){
        bzero(buff, RX_BUFF_SIZE);

        int n = read(handle->socket_descriptor, buff, sizeof(buff));
        if(n < 0){
            log_writen("error reading tcp socket");
            break;
        }
        else if(n == 0){
            break;
        }

        log_writen("got %d bytes from client", n);
        log_writen("content:");
        log_writen("%s", buff);

        process_data(buff, n);
    }

    remove_client_handler(handle);

    log_writen("client disconnected");

    return 0;
}