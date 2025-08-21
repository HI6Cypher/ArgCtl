#ifndef ARGCTL_H
#define ARGCTL_H

#include "types.h"
#include "allocator.h"
#include "utils/error_handler.h"
#include "utils/check_integer_type.h"
#include "utils/check_float_type.h"
#include "utils/check_bool_type.h"
#include "utils/check_string_type.h"
#include "utils/search_tools.h"
#include "utils/checksum.h"

#include <stdlib.h>
#include <string.h>

#define get_current_flow(ctl) (ctl->current_flow)
#define get_flow_help_message(flow) (flow->help)
#define print_flow_help(flow) printf(flow->help)
#define is_specified(arg) (arg->specified)
#define get_value_count(arg) (arg->nval)
#define get_max_value_count(arg) (arg->max_nval)
#define get_argument_help_message(arg) (arg->help)
#define print_arg_help(arg) printf(arg->help)

ArgCtl start_argctl(const unsigned char *prog, const unsigned char *msg);

void start_parser(ArgCtl *ctl, unsigned int argc, unsigned char *arg[]);

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
    const unsigned char *tname,
    const unsigned char *help,
    const unsigned int nval,
    const unsigned int max_nval,
    Types type,
    bool (*check_type)(void *val),
    bool required,
    void *default_val
);

Flag *add_flag(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarg,
    const unsigned char *tname,
    const unsigned char *help,
    bool required,
    bool default_val
);

Custom *get_option_value(Option *opt);

bool get_flag_value(Flag *flg);

void print_global_help_message(ArgCtl *ctl);

void print_flow_help_message(Flow *flow);

#endif
