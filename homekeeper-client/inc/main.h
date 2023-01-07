#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <threads.h>
#include "ed_crypto/ed25519.h"

typedef struct key_pair {
    uint8_t public_key[32];
    uint8_t private_key[64];
    unsigned long id;
} key_pair;

typedef struct client_key{
    uint8_t public_key[32];
    unsigned long id;
    unsigned long last_online;
    bool is_notified;
} client_key;

#endif