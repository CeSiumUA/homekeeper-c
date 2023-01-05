#include "notifier.h"

static thrd_t ch_thrd;
static bool is_thrd_active = true;

void notifier_start(void){
    thrd_create(&ch_thrd, notification_runner, NULL);
    thrd_detach(ch_thrd);
}

void notifier_stop(void){
    is_thrd_active = false;
}

static int notification_runner(void *arg){
    while(is_thrd_active){
        
    }
}