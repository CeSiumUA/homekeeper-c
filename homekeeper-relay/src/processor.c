#include "processor.h"

#define SIGNATURE_SIZE                  64
#define ARGUMENT_SIZE                   sizeof(u_long)
#define ID_SIZE                         sizeof(u_long)
#define MAX_TIME_DIFF_S                2

void process_data(const uint8_t *data, size_t data_size){

    uint8_t id[ID_SIZE];
    uint8_t argument[ARGUMENT_SIZE];
    uint8_t signature[SIGNATURE_SIZE];

    memcpy(id, data, ID_SIZE);
    memcpy(argument, data + ID_SIZE, ARGUMENT_SIZE);
    memcpy(signature, data + ARGUMENT_SIZE + ID_SIZE, SIGNATURE_SIZE);

    time_t curr_time = time(NULL);

    time_t client_time = *(time_t *)argument;

    time_t diff = labs(curr_time - client_time);

    log_writen("time diff: %lu", diff);

    if(diff > MAX_TIME_DIFF_S){
        return;
    }

    client_key cl_key;

    storage_get_pubkey(*(u_long *)id, &cl_key);

    if(!ed25519_verify(signature, argument, sizeof(argument), cl_key.public_key)){
        log_writen("ed25519 signature missmatch...");
        return;
    }

    cl_key.last_online = curr_time;

    if(cl_key.is_notified){
        tlbot_notify_device_back_online(cl_key.id);
    }

    cl_key.is_notified = false;

    storage_save_pubkey(&cl_key);
}