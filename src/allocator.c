#include "allocator.h"

static void alloc_flow(ArgCtl *ctl) {
    ctl->flows = (Flow *) realloc(ctl->flows, (ctl->flow_count + 1) * sizeof (char));
    if (ctl->flows == NULL)
        raise_realloc_error(__func__, "reallocation of new flow");
    return;
}

static Arg *alloc_arg(Flow *flow) {
    flow->args = (Arg *) realloc(flow->args, (flow->arg_count + 1) * sizeof (char));
    if (flow->args == NULL)
        raise_realloc_error(__func__, "reacllocation of new argument");
    return;
}

Flow *copy_flow(ArgCtl *ctl, Flow *flow) {
    alloc_flow(ctl);
    return (Flow *) memcpy(&ctl->flows[0], (unsigned char *) flow, sizeof (flow));
}

Arg *copy_arg(Flow *flow, Arg *arg) {
    alloc_arg(flow);
    return (Arg *) memcpy(&flow->args[0], (unsigned char *) arg, sizeof (arg));
}
