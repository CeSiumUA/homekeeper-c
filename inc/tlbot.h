#ifndef TLBOT_H_
#define TLBOT_H_

#include <stdio.h>
#include <stdbool.h>
#include <telebot/telebot.h>
#include "logger.h"
#include "config.h"

bool initialize_tlbot(void);
void destroy_bot(void);

#endif