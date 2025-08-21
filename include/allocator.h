#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "types.h"
#include "utils/error_handler.h"
#include <stdlib.h>

Flow *copy_flow(ArgCtl *ctl, Flow *flow);
Arg *copy_arg(Flow *flow, Arg *arg);

#endif
