#include "main.h"

int main(void){

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