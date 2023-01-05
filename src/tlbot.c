#include "tlbot.h"

#define TOKEN_BUFFER_HANDLE     1024

static telebot_handler_t handle;

bool initialize_tlbot(void){
    char token[TOKEN_BUFFER_HANDLE];
    if(!load_conf_value("TL_TOKEN", token, TOKEN_BUFFER_HANDLE)){
        return false;
    }

    telebot_error_e create_err = telebot_create(&handle, token);

    if(create_err != TELEBOT_ERROR_NONE){
        log_writen("error creating bot instance, error code: %d", create_err);
        telebot_destroy(handle);
        return false;
    }

    return true;
}

void destroy_bot(void){
    telebot_error_e destroy_err = telebot_destroy(handle);
    
    if(destroy_err != TELEBOT_ERROR_NONE){
        log_writen("failed to properly destroy a bot, error: %d", destroy_err);
    }
}