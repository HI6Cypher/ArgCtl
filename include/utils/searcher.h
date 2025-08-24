#ifndef SEARCHER_H
#define SEARCHER_H

#include "types.h"
#include "utils/checksum.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum meta_types {
    FLOW,
    INDEP_OPT,
    INDEP_FLAG,
    DEPEN_OPT,
    DEPEN_FLAG
};

struct global_search_t {
    enum meta_types mt;
    bool found;
    void *loc;
};

Flow *search_inflows(Flow *flows, size_t count, const unsigned char *str);

Arg *search_inlargs(Arg *args, size_t count, const unsigned char *str);

Arg *search_insargs(Arg *args, size_t count, const unsigned char *str);

struct global_search_t global_search(ArgCtl *ctl, const unsigned char *str, bool flow_specified);

#endif
