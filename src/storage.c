#include "storage.h"

#define HOME_BUFFER_SIZE    2048
#define APP_FOLDER_SIZE     2064

static char app_folder[] = "/.homekeeper-arp";
static char records_folder[] = "/records";
static char app_folder_absolute[HOME_BUFFER_SIZE + sizeof(app_folder)] = {0};
static char records_folder_absolute[sizeof(app_folder_absolute) + sizeof(records_folder)] = {0};

static void ensure_dir_created(const char *dir);

void storage_init(void){

    if(!load_environment_variable("HOME", app_folder_absolute, HOME_BUFFER_SIZE)){
        log_writen("failed to initialize storage");
        exit(-1);
    }

    strcat(app_folder_absolute, app_folder);

    ensure_dir_created(app_folder_absolute);

    strcat(records_folder_absolute, app_folder_absolute);
    strcat(records_folder_absolute, records_folder);

    ensure_dir_created(records_folder_absolute);
}

bool storage_get_pubkey(unsigned long id, client_key *client){
    char separator[] = "/";
    char file_path[sizeof(records_folder_absolute) + sizeof(id)] = {0};
    char file_name[sizeof(id)] = {0};
    sprintf(file_name, "%d", id);
    strcat(file_path, records_folder_absolute);
    strcat(file_path, separator);
    strcat(file_path, file_name);
    
    FILE *fd = fopen(file_path, "r");
    if(fd == NULL){
        fclose(fd);
        return false;
    }
    
    fread(client, sizeof(client_key), 1, fd);

    fclose(fd);

    return true;
}

void storage_save_pubkey(client_key *client){
    char separator[] = "/";
    char file_path[sizeof(records_folder_absolute) + sizeof(client -> id)] = {0};
    char file_name[sizeof(client -> id)] = {0};
    sprintf(file_name, "%d", client -> id);
    strcat(file_path, records_folder_absolute);
    strcat(file_path, separator);
    strcat(file_path, file_name);

    FILE *fd = fopen(file_path, "wb");

    fwrite(client, sizeof(client_key), 1, fd);

    fclose(fd);
}

static void ensure_dir_created(const char *dir){
    struct stat st = {0};

    if(stat(dir, &st) == -1){
        mkdir(dir, 0700);
    }
}