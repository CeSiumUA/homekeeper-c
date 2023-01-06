#include "notifier.h"

#define MAX_TIME_DIFF_MS        120000

static thrd_t ch_thrd;
static bool is_thrd_active = true;

static int notification_runner(void *arg);

void notifier_start(void){
    thrd_create(&ch_thrd, notification_runner, NULL);
    thrd_detach(ch_thrd);
}

void notifier_stop(void){
    is_thrd_active = false;
}

static int notification_runner(void *arg){
    while(is_thrd_active){

        int files_count;
        char **records = storage_get_records(&files_count);

        for(int i = 0; i < files_count; i++){

            unsigned long id = atol(records[i]);

            client_key cl_key;

            storage_get_pubkey(id, &cl_key);

            ulong diff = time(NULL) - cl_key.last_online;

            if(diff > MAX_TIME_DIFF_MS && !cl_key.is_notified){
                tlbot_notify(cl_key.id, diff);
                cl_key.is_notified = true;
                storage_save_pubkey(&cl_key);
            }

            free(records[i]);
        }
        free(records);

        log_writen("waiting another run...");
        struct timespec ts = {.tv_sec = 30};
        thrd_sleep(&ts, NULL);
    }

    return 0;
}