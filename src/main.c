#include "main.h"

int main(void){

    char buff[2048];

    load_conf_value("PULSE_SERVER", buff, sizeof(buff));
    
    return 0;

    if(!initialize_tlbot()){
        destroy_bot();
        write_logn("bot initialization failed, exiting");
        return -1;
    }

    free_resources();

    return 0;
}

void free_resources(void){
    destroy_bot();
}