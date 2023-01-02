#include <stdio.h>
#include <telebot/telebot.h>

int main(void){

    FILE *fp = fopen(".token", "r");

    if(fp == NULL){
        printf("token file not found!\n");
        return -1;
    }

    char token[1024];

    if(fscanf(fp, "%s", token) == 0){
        printf("failed to read a token!\n");
        fclose(fp);
        return -1;
    }

    fclose(fp);
    printf("token read successfully! token: %s\n", token);

    telebot_handler_t handle;

    telebot_error_e create_err = telebot_create(&handle, token);

    if(create_err != TELEBOT_ERROR_NONE){
        printf("error creating bot instance\n");
        telebot_destroy(handle);
        return -1;
    }

    printf("bot instance created successfully\n");
    return 0;
}