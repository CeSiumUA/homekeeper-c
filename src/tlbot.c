#include "tlbot.h"

static telebot_handler_t handle;

bool initialize_tlbot(void){
    FILE *fp = fopen(".token", "r");

    if(fp == NULL){
        write_logn("token file not found!");
        return false;
    }

    char token[1024];

    if(fscanf(fp, "%s", token) == 0){
        write_logn("failed to read a token!");
        fclose(fp);
        return false;
    }

    fclose(fp);
    write_logn("token read successfully! token: %s", token);

    telebot_error_e create_err = telebot_create(&handle, token);

    if(create_err != TELEBOT_ERROR_NONE){
        write_logn("error creating bot instance, error code: %d", create_err);
        telebot_destroy(handle);
        return false;
    }

    return true;
}

void destroy_bot(void){
    telebot_error_e destroy_err = telebot_destroy(handle);
    
    if(destroy_err != TELEBOT_ERROR_NONE){
        write_logn("failed to properly destroy a bot, error: %d", destroy_err);
    }
}