#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include "logger.h"

bool server_init(void);
void server_close(void);
void server_listen(void);

#endif