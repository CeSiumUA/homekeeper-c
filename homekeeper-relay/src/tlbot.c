#include "tlbot.h"

#define TOKEN_BUFFER_HANDLE     1024
#define CHAT_ID_BUFFER_HANDLE   32
#define MESSAGE_SIZE            4096

static bool get_chat_id(long long *id);
static bool initialize_tlbot(telebot_handler_t *handle);
static void destroy_bot(telebot_handler_t *handle);
static void send_message(char *message);

void tlbot_notify_device_offline(unsigned long id, unsigned long time_diff){

    char message[MESSAGE_SIZE];

    ulong time_diff_mins = time_diff / 60;

    sprintf(message, "Device %lu is offline for %lu minutes", id, time_diff_mins);

    send_message(message);
}

void tlbot_notify_device_back_online(unsigned long id){

    char message[MESSAGE_SIZE];

    sprintf(message, "Device %lu is back online", id);

    send_message(message);
}

void tlbot_notify_service_started(void){
  char *message = "Server initialized and started";

  send_message(message);
}

static void send_message(char *message){
  long long chat_id;

  if(!get_chat_id(&chat_id)){
    return;
  }

  telebot_handler_t handle;

  if(!initialize_tlbot(&handle)){
    destroy_bot(&handle);
    log_writen("bot initialization failed");
    return;
  }

  telebot_error_e err = telebot_send_message(handle, chat_id, message, "HTML", false, false, -1, "");

  if(err != TELEBOT_ERROR_NONE){
    log_writen("error sending message to chat");
  }

  destroy_bot(&handle);

}

static void destroy_bot(telebot_handler_t *handle){
    telebot_error_e destroy_err = telebot_destroy(*handle);
    
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

static bool initialize_tlbot(telebot_handler_t *handle){
  char token[TOKEN_BUFFER_HANDLE];
  if(!load_conf_value("TL_TOKEN", token, TOKEN_BUFFER_HANDLE)){
    return false;
  }

  telebot_error_e create_err = telebot_create(handle, token);

  if(create_err != TELEBOT_ERROR_NONE){
    log_writen("error creating bot instance, error code: %d", create_err);
    telebot_destroy(*handle);
    return false;
  }

  return true;
}