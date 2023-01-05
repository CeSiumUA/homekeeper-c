#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include "logger.h"

bool load_conf_value(const char* key, char* const buffer, size_t buffer_size);
bool load_environment_variable(const char *key, char *buff, size_t buff_size);

#endif