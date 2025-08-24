#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "types.h"
#include <stdlib.h>
#include <errno.h>

struct typecheck_t typecheck_integer(void *val);

struct typecheck_t typecheck_float(void *val);

#endif
