#include "tlbot.h"

#define TOKEN_BUFFER_HANDLE     1024
#define CHAT_ID_BUFFER_HANDLE   32
#define MESSAGE_SIZE            4096

static telebot_handler_t handle;
static bool get_chat_id(long long *id);

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

void tlbot_notify_device_offline(unsigned long id, unsigned long time_diff){
    long long chat_id;

    if(!get_chat_id(&chat_id)){
        return;
    }

    char message[MESSAGE_SIZE];

    ulong time_diff_mins = time_diff / 60;

    sprintf(message, "Device %lu is offline for %lu minutes", id, time_diff_mins);

    telebot_error_e err = telebot_send_message(handle, chat_id, message, "HTML", false, false, -1, "");

    if(err != TELEBOT_ERROR_NONE){
        log_writen("error sending message to chat");
    }
}

void tlbot_notify_device_back_online(unsigned long id){
    long long chat_id;

    if(!get_chat_id(&chat_id)){
        return;
    }

    char message[MESSAGE_SIZE];

    sprintf(message, "Device %lu is back online", id);

    telebot_error_e err = telebot_send_message(handle, chat_id, message, "HTML", false, false, -1, "");

    if(err != TELEBOT_ERROR_NONE){
        log_writen("error sending message to chat");
    }
}

void destroy_bot(void){
    telebot_error_e destroy_err = telebot_destroy(handle);
    
    if(destroy_err != TELEBOT_ERROR_NONE){
        log_writen("failed to properly destroy a bot, error: %d", destroy_err);
    }
}

static bool get_chat_id(long long *id){
    char chat_id_str[CHAT_ID_BUFFER_HANDLE];
    if(!load_conf_value("TL_CHAT", chat_id_str, CHAT_ID_BUFFER_HANDLE)){
        return false;
    }

    *id = atoll(chat_id_str);

    return true;
}