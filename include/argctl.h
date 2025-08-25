#ifndef ARGCTL_H
#define ARGCTL_H

#include "types.h"
#include "allocator.h"
#include "utils/error_handler.h"
#include "utils/typecheck.h"
#include "utils/searcher.h"
#include "utils/checksum.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define get_current_flow(ctl) (ctl->current_flow)
#define get_current_flow_name(ctl) (ctl.current_flow->name)
#define get_flow_help_message(flow) (flow->help)
#define print_flow_help(flow) printf(flow->help)
#define is_specified(arg) (arg->specified)
#define get_argument_help_message(arg) (arg->help)
#define print_arg_help(arg) printf(arg->help)
#define get_flag_value(flag) ((flag->specified) ? flag->value.bool_val : flag->default_val.bool_val)

ArgCtl start_argctl(const unsigned char *prog, const unsigned char *msg);

void start_parser(ArgCtl *ctl, unsigned int argc, unsigned char *arg[]);

void end_argctl(ArgCtl *ctl);

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
    Types type,
    struct typecheck_t (*typecheck)(void *val),
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

Custom get_option_value(Option *opt);

void print_global_help_message(ArgCtl *ctl);

void print_flow_help_message(Flow *flow);

#endif
