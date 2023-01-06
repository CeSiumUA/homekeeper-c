#include "main.h"

int main(void){
    
    storage_init();

    if(!initialize_tlbot()){
        destroy_bot();
        log_writen("bot initialization failed, exiting");
        return -1;
    }

    notifier_start();

    if(!server_init()){
        server_close();
        log_writen("socket initialization failed, exiting");
        return -1;
    }

    server_listen();

    log_writen("type q to exit a server");

    while(1){
        char chr;
        scanf("%c", &chr);
        if (chr == 'q'){
            break;
        }
    }

    free_resources();

    return 0;
}

void free_resources(void){
    destroy_bot();
    server_close();
    notifier_stop();
}