#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdarg.h>

void write_log(const char * txt, ...);
void write_logn(const char * txt, ...);

#endif