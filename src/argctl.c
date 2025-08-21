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

static void create_indep_help_argument(ArgCtl *ctl) {
    Flag flag;
    unsigned char help_message[] = "This flag shows the flows and the independent arguments";
    strcpy(flag.larg, "--help");
    strcpy(flag.sarg, "-h");
    flag.help = (unsigned char *) malloc(sizeof (help_message));
    if (!flag.help)
        raise_malloc_error("create_indep_help_argument");
    else
        strcpy(flag.help, help_message);
    flag.larg_cksum = checksum(flag.larg, strlen(flag.larg) + 1);
    flag.sarg_cksum = checksum(flag.sarg, strlen(flag.sarg) + 1);
    flag.type = BOOL;
    flag.check_type = check_bool_type;
    flag.required = false;
    flag.default_val.bool_val = false;
    alloc_arg(&ctl->indep);
    copy_arg(&ctl->indep, &flag);
    return;
}

static void copy_help_message(ArgCtl *ctl, const unsigned char *help) {
    ctl->help = (unsigned char *) malloc(strlen(help) + 1);
    if (!ctl->help)
        raise_malloc_error("append_help_message");
    else
        strcpy(ctl->help, help);
    return;
}

ArgCtl start_argctl(const unsigned char *prog, const unsigned char *msg) {
    ArgCtl ctl;
    strncpy(ctl.name, prog, sizeof (ctl.name));
    create_indep_flow(&ctl);
    create_indep_help_argument(&ctl);
    copy_help_message(&ctl, msg);
    return ctl;
}

static void copy_flow_name(Flow *flow, const unsigned char *name) {
    strcpy(flow->name, name);
    flow->cksum = checksum(name, strlen(name) + 1);
    return;
}

static void copy_flow_help_message(Flow *flow, const unsigned char *help) {
    flow->help = (unsigned char *) malloc(strlen(help) + 1);
    if (!flow->help)
        raise_malloc_error("copy_flow_help_message");
    else
        strcpy(flow->help, help);
    return;
}

static void create_flow_help_argument(Flow *flow) {
    Flag flag;
    unsigned char help_message[] = "This flag shows the help message";
    strcpy(flag.larg, "--help");
    strcpy(flag.sarg, "-h");
    flag.help = (unsigned char *) malloc(sizeof (help_message));
    if (!flag.help)
        raise_malloc_error("create_flow_help_argument");
    else
        strcpy(flag.help, help_message);
    flag.larg_cksum = checksum(flag.larg, strlen(flag.larg) + 1);
    flag.sarg_cksum = checksum(flag.sarg, strlen(flag.sarg) + 1);
    flag.type = BOOL;
    flag.check_type = check_bool_type;
    flag.required = false;
    flag.default_val.bool_val = false;
    alloc_arg(flow);
    copy_arg(flow, &flag);
    return;
}

Flow *add_flow(
    ArgCtl *ctl,
    const unsigned char *name,
    const unsigned char *help
) {
    Flow flow;
    copy_flow_name(&flow, name);
    copy_flow_help_message(&flow, help);
    create_flow_help_argument(&flow);
    return copy_flow(ctl, &flow);
}

static void copy_arg_names(Arg *arg, const unsigned char *larg, const unsigned char *sarg, unsigned char *tname) {
    strcpy(arg->larg, larg);
    strcpy(arg->sarg, sarg);
    strcpy(arg->tname, tname);
    arg->larg_cksum = checksum(arg->larg, strlen(arg->larg) + 1);
    arg->sarg_cksum = checksum(arg->sarg, strlen(arg->sarg) + 1);
    return;
}

static void copy_arg_help_message(Arg *arg, const unsigned char *help) {
    arg->help = (unsigned char *) malloc(strlen(help) + 1);
    if (!arg->help)
        raise_malloc_error("copy_arg_help_message");
    else
        strcpy(arg->help, help);
    return;
}

static void set_default_value(Arg *arg, Types type, void *default_val) {
    switch (type) {
        case INTEGER :
            arg->default_val.integer_val = *(signed long *) default_val;
            break;
        case FLOAT :
            arg->default_val.float_val = *(float *) default_val;
            break;
        case BOOL :
            arg->default_val.bool_val = *(bool *) default_val;
            break;
        case STRING :
            arg->default_val.string_val = (unsigned char *) default_val;
            break;
        case CUSTOM :
        default :
            arg->default_val.custom_val = (unsigned char *) default_val;
            break;
    }
    return;
}

Option *add_option(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarg,
    const unsigned char *tname,
    const unsigned char *help,
    const unsigned int max_nval,
    Types type,
    bool (*check_type)(void *val),
    bool required,
    void *default_val
) {
    Option opt;
    copy_arg_names(&opt, larg, sarg, tname);
    copy_arg_help_message(&opt, help);
    set_default_value(&opt, type, default_val);
    opt.max_nval = max_nval;
    opt.type = type;
    opt.check_type = check_type;
    opt.required = required;
    return copy_arg(flow, &opt);
}

Flag *add_flag(
    Flow *flow,
    const unsigned char *larg,
    const unsigned char *sarg,
    const unsigned char *tname,
    const unsigned char *help,
    bool required,
    bool default_val
) {
    Flag flag;
    copy_arg_names(&flag, larg, sarg, tname);
    copy_arg_help_message(&flag, help);
    flag.default_val.bool_val = default_val;
    flag.type = BOOL;
    flag.check_type = check_bool_type;
    flag.required = required;
    return copy_arg(flow, &flag);
}


Custom *get_option_value(Option *opt) {
    return (opt->specified) ? &opt->value : &opt->default_val;
}

bool get_flag_value(Flag *flag) {
    return (flag->specified) ? flag->value.bool_val : flag->default_val.bool_val;
}

void print_global_help_message(ArgCtl *ctl) {
    unsigned int i;
    printf("The global help message powered by ArgCtl\n");
    printf("GitHub : https://github.com/HI6Cypher/ArgCtl\n");
    printf("\n%s\n", ctl->help);
    printf("Flows :\n");
    for (i = 0; i < ctl->flow_count; i++)
        printf("\t%s : %s\n", ctl->flows[i].name, ctl->flows[i].help);
    printf("Arguments :\n");
    for (i = 0; i < ctl->indep.arg_count; i++) {
        if (ctl->indep->args[i].type == BOOL)
            printf(
                "\t%s %s : %s\n",
                ctl->indep->args[i].sarg,
                ctl->indep->args[i].larg,
                ctl->indep->args[i].help
            );
        else
            printf(
                "\t%s %s  <%s> : %s\n",
                ctl->indep->args[i].sarg,
                ctl->indep->args[i].larg,
                ctl->indep->args[i].tname,
                ctl->indep->args[i].help,
            );
    }
    return;
}

void print_flow_help_message(Flow *flow) {
    unsigned int i;
    printf("The %s help message powered by ArgCtl\n");
    printf("GitHub : https://github.com/HI6Cypher/ArgCtl\n");
    printf("\n%s\n", flow->help);
    printf("Arguments :\n");
    for (i = 0; i < flow->arg_count; i++) {
        if (flow->args[i].type == BOOL)
            printf(
                "\t%s %s : %s\n",
                flow->args[i].sarg,
                flow->args[i].larg,
                flow->args[i].help
            );
        else
            printf(
                "\t%s %s  <%s> : %s\n",
                flow->args[i].sarg,
                flow->args[i].larg,
                flow->args[i].tname,
                flow->args[i].help,
            );
    }
    return;
}
