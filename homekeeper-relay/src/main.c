#include "main.h"

int main(void){

    log_writen("homekeeper relay is going to initialize...");
    
    storage_init();

    notifier_start();

    if(!server_init()){
        server_close();
        log_writen("socket initialization failed, exiting");
        return -1;
    }

    server_listen();

    log_writen("going to endless loop...");

    tlbot_notify_service_started();

    while (1){
        struct timespec ts = {.tv_sec = 1};
        thrd_sleep(&ts, NULL);
    }

    log_writen("finished");

    free_resources();

    return 0;
}

void free_resources(void){
    server_close();
    notifier_stop();
}