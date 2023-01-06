#ifndef NOTIFIER_H_
#define NOTIFIER_H_

#include <threads.h>
#include <stdbool.h>
#include "tlbot.h"
#include "storage.h"

void notifier_start(void);
void notifier_stop(void);

#endif