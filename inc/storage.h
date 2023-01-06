#ifndef STORAGE_H_
#define STORAGE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "config.h"

typedef struct client_key{
    uint8_t public_key[32];
    unsigned long id;
    unsigned long last_online;
} client_key;

void storage_init(void);

bool storage_get_pubkey(unsigned long id, client_key *client);
void storage_save_pubkey(client_key *client);
char** storage_get_records(int *n);

#endif
