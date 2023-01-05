#include "storage.h"

#define HOME_BUFFER_SIZE    2048
#define APP_FOLDER_SIZE     2064

static char app_folder[] = "/.homekeeper-arp";
static char app_folder_absolute[HOME_BUFFER_SIZE + sizeof(app_folder)] = {0};

static void ensure_dir_created(const char *dir);

void storage_init(void){

    if(!load_environment_variable("HOME", app_folder_absolute, HOME_BUFFER_SIZE)){
        log_writen("failed to initialize storage");
        exit(-1);
    }

    strcat(app_folder_absolute, app_folder);

    ensure_dir_created(app_folder_absolute);
}

bool storage_get_pubkey(unsigned long id, client_key *client){
    char separator[] = "/";
    char file_path[sizeof(app_folder_absolute) + sizeof(id)] = {0};
    char file_name[sizeof(id)];
    sprintf(file_name, "%d", id);
    strcat(file_path, app_folder_absolute);
    strcat(file_path, separator);
    strcat(file_path, file_name);
    FILE *fd = fopen(file_path, "r");
    if(fd == NULL){
        fclose(fd);
        return false;
    }
    //TODO find better approach...
    size_t read_n = fread(client->public_key, sizeof(uint8_t), sizeof(client->public_key), fd);
    if(read_n < sizeof(client->public_key)){
        close(fd);
        return false;
    }
    fscanf(fd, "%lu\n", client->id);
    fscanf(fd, "%lu\n", client->last_online);

    fclose(fd);

    return true;
}

void storage_save_pubkey(client_key *client){
    char separator[] = "/";
    char file_path[sizeof(app_folder_absolute) + sizeof(id)] = {0};
    char file_name[sizeof(id)];
    sprintf(file_name, "%d", id);
    strcat(file_path, app_folder_absolute);
    strcat(file_path, separator);
    strcat(file_path, file_name);
    FILE *fd = fopen(file_path, "r");
}

static void ensure_dir_created(const char *dir){
    struct stat st = {0};

    if(stat(dir, &st) == -1){
        mkdir(dir, 0700);
    }
}