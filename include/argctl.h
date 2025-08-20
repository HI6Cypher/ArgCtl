#ifndef ARGCTL_H
#define ARGCTL_H

#include "types.h"
#include "allocator.h"
#include "utils/error_handles.h"
#include "utils/check_integer_type.h"
#include "utils/check_string_type.h"
#include "utils/check_float_type.h"
#include "utils/check_bool_type.h"
#include "utils/search_tools.h"
#include "utils/checksum.h"

#include <stdlib.h>
#include <string.h>

ArgCtl start_argctl(const unsigned char *msg);

void start_parser(ArgCtl *ctl, unsigned int argc, unsigned char *arg[]);

void end_arg_ctl(ArgCtl *ctl);

Flow *add_flow(
    ArgCtl *ctl,
    const unsigned char *name,
    const unsigned char *help,
);

Option *add_option(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarg,
    const unsigned char *help,
    const unsigned int nval,
    Types type,
    bool (*check_type)(void *val),
    bool required,
    void *default_val,
);

Flag *add_flag(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarp,
    const unsigned char *help,
    bool required,
    bool default_val
);

void get_option_value(Option *opt, void *val);

void get_flag_value(Flag *flg, bool *val);

#endif
