#include "logger.h"

void write_log(const char * txt, ...){
    va_list va;

    va_start(va, txt);
    vprintf(txt, va);
    va_end(va);
}

void write_logn(const char * txt, ...){
    va_list va;

    va_start(va, txt);
    vprintf(txt, va);
    va_end(va);
    printf("\n");
}