#include "logger.h"

void log_write(const char * txt, ...){
    va_list va;

    va_start(va, txt);
    vprintf(txt, va);
    va_end(va);
}

void log_writen(const char * txt, ...){
    va_list va;

    va_start(va, txt);
    vprintf(txt, va);
    va_end(va);
    printf("\n");
}