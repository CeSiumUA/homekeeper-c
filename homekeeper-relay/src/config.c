#include "config.h"

bool load_conf_value(const char* key, char* const buffer, size_t buffer_size){

    if (load_environment_variable(key, buffer, buffer_size)){
        return true;
    }

    int key_length = strlen(key);
    char key_buff[key_length + 1];
    strcpy(key_buff, ".");
    strcat(key_buff, key);
    FILE *fd = fopen(key_buff, "r");
    if(fd == NULL){
        log_writen("can not find the file specified (%s)", key_buff);
        return false;
    }
    int scan_buff_size = fscanf(fd, "%s", buffer);
    fclose(fd);
    if(scan_buff_size >= buffer_size || scan_buff_size == 0){
        log_writen("buffer too small for %s value, exceeding %d, with size: %d, or can not read file", key, buffer_size, scan_buff_size);
        return false;
    }
    return true;
}

bool load_environment_variable(const char *key, char *buff, size_t buff_size){
    if(!getenv(key)){
        return false;
    }
    int env_size = snprintf(buff, buff_size, "%s", getenv(key));
    if(env_size >= buff_size){
        log_writen("buffer too small for %s value, exceeding %d", key, buff_size);
        return false;
    }

    return true;
}