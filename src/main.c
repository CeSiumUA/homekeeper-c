#include "main.h"

int main(void){

    if(!initialize_tlbot()){
        destroy_bot();
        log_writen("bot initialization failed, exiting");
        return -1;
    }

    if(!server_init()){
        server_close();
        log_writen("socket initialization failed, exiting");
        return -1;
    }

    free_resources();

    return 0;
}

void free_resources(void){
    destroy_bot();
    server_close();
}