#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdarg.h>

void log_write(const char * txt, ...);
void log_writen(const char * txt, ...);

#endif