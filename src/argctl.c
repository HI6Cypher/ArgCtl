#include "argctl.h"

static void create_indep_flow(ArgCtl *ctl) {
    unsigned char help_message[] = "The independent flow indicates that the arguments are independent";
    strcpy(ctl->indep.name, "indep");
    ctl->indep.help = (unsigned char *) malloc(sizeof (help_message));
    if (!ctl->indep.help)
        raise_malloc_error("create_indep_flow()"); /* TODO */
    else
        strcpy(ctl->indep.help, help_message);
    return;
}

static void create_indep_help_argument(Argctl *ctl) {
    Flag flag;
    unsigned char help_message[] = "This flag shows the flows and the independent arguments";
    strcpy(flag.larg, "--help");
    strcpy(flag.sarg, "-h");
    flag.help = (unsigned char *) malloc(sizeof (help_message));
    if (!flag.help)
        raise_malloc_error("create_indep_help_argument");
    else
        strcpy(flag.help, help_message);
    flag.larg_cksum = checksum(flag.larg);
    flag.sarg_cksum = checksum(flag.sarg);
    flag.type = BOOL;
    flag.check_type = check_bool_type;
    flag.required = false;
    flag.default_val = false;
    return;
}

static void append_help_message(ArgCtl *ctl, const unsigned char *help) {
    ctl->help = (unsigned char *) malloc(strlen(help) + 1);
    if (!ctl->help)
        raise_malloc_error("append_help_message");
    else
        strcpy(ctl->help, help);
    return;
}

ArgCtl start_argctl(const unsigned char *msg) {
    ArgCtl ctl;
    create_indep_flow(&ctl);
    create_indep_help_argument(&ctl);
    append_help_message(&ctl, msg);
    return ctl;
}

static void copy_flow_name(Flow *flow, const unsigned char *name);
static void copy_flow_help_message(Flow *flow, const unsigned char *help);
static void calculate_flow_cksum(const unsigned char *name);
static void create_flow_help_argument(Flow *flow);
static Flow *copy_flow(ArgCtl *ctl, Flow *flow);

Flow *add_flow(
    ArgCtl *ctl,
    const unsigned char *name,
    const unsigned char *help,
) {
    Flow flow;
    copy_flow_name(&flow, name);
    copy_flow_help_message(&flow, help);
    calculate_flow_cksum(&flow, name);
    create_flow_help_argument(&flow);
    return copy_flow(ctl, &flow);
}

static void copy_arg_names(Arg *arg, const unsigned char *larg, const unsigned char *sarg);
static void copy_arg_help_message(Arg *arg, const unsigned char *help);
static void calculate_arg_cksum(Arg *arg, const unsigned char *larg, const unsigned char *sarg);
static void set_default_value(Arg *arg, Types type, void *default_val);
static Arg *copy_arg(Flow *flow, Arg *arg);

Option *add_option(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarg,
    const unsigned char *help,
    const unsigned int nargs,
    Types type,
    bool (*check_type)(void *val),
    bool required,
    void *default_val,
) {
    Option opt;
    copy_arg_names(&opt, larg, sarg);
    copy_arg_help_message(&opt, help);
    calculate_arg_cksum(&opt, larg, sarg);
    set_default_value(&opt, type, default_val);
    opt.type = type;
    opt.check_type = check_type;
    opt.required = required;
    return copy_arg(flow, &opt);
}

Flag *add_flag(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarp,
    const unsigned char *help,
    bool required,
    bool default_val
) {
    Flag flag;
    copy_arg_names(&flag, larg, sarg);
    copy_arg_help_message(&flag, help);
    calculate_arg_cksum(&flag, larg, sarg);
    opt.default_val = default_val;
    opt.type = BOOL;
    opt.check_type = check_bool_type;
    opt.required = required;
    return copy_arg(flow, &flag);
}
