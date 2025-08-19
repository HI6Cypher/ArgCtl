#ifndef ARGCTL_H
#define ARGCTL_H

#include "types.h"
#include "utils/checksum.h"
#include "utils/check_integer_type.h"
#include "utils/check_string_type.h"
#include "utils/check_float_type.h"
#include "utils/check_bool_type.h"

ArgCtl start_argctl(const unsigned char *msg);

void end_arg_ctl(ArgCtl *ctl);

Flow *add_flow(
    ArgCtl *ctl,
    const unsigned char *name,
    const unsigned char *help
);

Option *add_option(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarg,
    const unsigned char *type,
    const unsigned char *help,
    const unsigned int nargs,
    Bool (*check_type)(void *val),
    Bool required,
    void *default_val,
);

Flag *add_flag(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarp,
    const unsigned char *help,
    Bool required,
    Bool default_val
);

void get_option_value(Option *opt, void *val);

void get_flag_value(Flag *flg, Bool *val);

#endif
