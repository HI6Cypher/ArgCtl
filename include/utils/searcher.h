#ifndef SEARCHER_H
#define SEARCHER_H

#include "types.h"

Flow *search_flow(ArgCtl *ctl, const unsigned char *flow);
Arg *search_argument(Flow *flow, const unsigned char *arg);

#endif
