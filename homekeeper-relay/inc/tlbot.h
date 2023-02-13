#ifndef TLBOT_H_
#define TLBOT_H_

#include <stdio.h>
#include <stdbool.h>
#include <telebot/telebot.h>
#include "logger.h"
#include "config.h"

void tlbot_notify_device_offline(unsigned long id, unsigned long time_diff);
void tlbot_notify_device_back_online(unsigned long id);

#endif