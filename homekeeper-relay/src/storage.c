#include "storage.h"

#define HOME_BUFFER_SIZE    2048
#define APP_FOLDER_SIZE     2064

static char app_folder[] = "/.homekeeper-relay";
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
    sprintf(file_name, "%lu", id);
    strcat(file_path, records_folder_absolute);
    strcat(file_path, separator);
    strcat(file_path, file_name);
    
    log_writen("opening public key file: %s", file_path);
    FILE *fd = fopen(file_path, "r");
    if(fd == NULL){
        log_writen("public key file not found");
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
    sprintf(file_name, "%lu", client -> id);
    strcat(file_path, records_folder_absolute);
    strcat(file_path, separator);
    strcat(file_path, file_name);

    FILE *fd = fopen(file_path, "wb");

    fwrite(client, sizeof(client_key), 1, fd);

    fclose(fd);
}

char** storage_get_records(int *n){
    DIR *dir = opendir(records_folder_absolute);
    if(dir == NULL){
        return NULL;
    }

    struct dirent *direntry;

    int allocated_cnt = 10;
    int files_cnt = 0;

    char **storage = malloc(sizeof(char*) * allocated_cnt);

    while((direntry = readdir(dir)) != NULL){
        if(direntry->d_type != DT_REG){
            continue;
        }

        files_cnt++;
        if(files_cnt > allocated_cnt){
            allocated_cnt *= 2;
            storage = realloc(storage, allocated_cnt);
        }

        char *file_name = malloc(sizeof(char) * sizeof(direntry->d_name));
        strcpy(file_name, direntry->d_name);

        storage[files_cnt - 1] = file_name;
    }

    closedir(dir);

    *n = files_cnt;

    return storage;
}

static void ensure_dir_created(const char *dir){
    struct stat st = {0};

    if(stat(dir, &st) == -1){
        mkdir(dir, 0700);
    }
}