#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <err.h>
#include <errno.h>

#define MALLOC_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\t%s\n\tat func \e[1;93m%s()\e[0m line \e[1;93m%d\e[0m in file \e[1;93m%s\e[0m\n"

#define raise_malloc_error(pos)\
    do {raise_global_error(pos, MALLOC_ERROR_MSG);} while (0)

void raise_global_error(const unsigned char *pos, const unsigned char *msg);

#endif
