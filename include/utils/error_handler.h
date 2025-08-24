#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define GLOBAL_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\t%s\n\tat func \e[1;93m%s()\e[0m line \e[1;93m%d\e[0m in file \e[1;93m%s\e[0m\n"
#define MALLOC_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\tInsufficient memory, unable to allocate enough memory inside function %s() for %s\n\tOSError[%d] %s\n"
#define REALLOC_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\tInsufficient memory, unable to reacllote enough memory inside fucntion %s() for %s\n\t OSError[%d %s\n"
#define NOVALUE_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\tMissing value for option %s, try --help or -h for more information\n"
#define CONFLICT_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\tThe Options %s/%s and %s/%s cannot be used together, try --help or -h for more information\n"
#define INVALID_TYPE_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\tInvalid value for option %s/%s <%s>, try --help or -h for more information\n"
#define NOTFOUND_ERROR_MSG "[\e[1;31m!\e[0m] Error : \n\tUnknown argument %s, try --help or -h for more information\n"

void raise_global_error(const unsigned char *pos, const unsigned char *msg);

void raise_malloc_error(const unsigned char *pos, const unsigned char *reason);

void raise_realloc_error(const unsigned char *pos, const unsigned char *reason);

void raise_novalue_error(const unsigned char *arg_name);

void raise_conflict_error(const unsigned char *f_larg, const unsigned char *f_sarg, const unsigned char *s_larg, const unsigned char *s_sarg);

void raise_invalid_type_error(const unsigned char *larg, const unsigned char *sarg, const unsigned char *tname);

void raise_notfound_error(const unsigned char *arg_name);

#endif
