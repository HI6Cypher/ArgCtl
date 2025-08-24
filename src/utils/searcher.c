#include "utils/searcher.h"

static signed int qsort_compar_flow(const void *x, const void *y) {
    return ((Flow *) x)->cksum - ((Flow *) y)->cksum;
}

static signed int bsearch_compar_flow(const void *x, const void *y) {
    return *(unsigned short *) x - ((Flow *) y)->cksum;
}

Flow *search_inflows(Flow *flows, size_t count, const unsigned char *str) {
    unsigned short cksum = checksum(str, strlen(str) + 1);
    qsort(flows, count, sizeof (Flow), qsort_compar_flow);
    Flow *loc = bsearch(&cksum, flows, count, sizeof (Flow), bsearch_compar_flow);
    return loc;
}

static signed int qsort_compar_larg(const void *x, const void *y) {
    return ((Arg *) x)->larg_cksum - ((Arg *) y)->larg_cksum;
}

static signed int bsearch_compar_larg(const void *x, const void *y) {
    return *(unsigned short *) x - ((Arg *) y)->larg_cksum;
}

Arg *search_inlargs(Arg *args, size_t count, const unsigned char *str) {
    unsigned short cksum = checksum(str, strlen(str) + 1);
    qsort(args, count, sizeof (Arg), qsort_compar_larg);
    Arg *loc = bsearch(&cksum, args, count, sizeof (Arg), bsearch_compar_larg);
    return loc;
}

static signed int qsort_compar_sarg(const void *x, const void *y) {
    return ((Arg *) x)->sarg_cksum - ((Arg *) y)->sarg_cksum;
}

static signed int bsearch_compar_sarg(const void *x, const void *y) {
    return *(unsigned short *) x - ((Arg *) y)->sarg_cksum;
}

Arg *search_insargs(Arg *args, size_t count, const unsigned char *str) {
    unsigned short cksum = checksum(str, strlen(str) + 1);
    qsort(args, count, sizeof (Arg), qsort_compar_sarg);
    Arg *loc = bsearch(&cksum, args, count, sizeof (Arg), bsearch_compar_sarg);
    return loc;
}

struct global_search_t global_search(ArgCtl *ctl, const unsigned char *str, bool flow_specified) {
    struct global_search_t result;
    if (flow_specified) {
        Arg *arg, *larg, *sarg;
        larg = search_inlargs(ctl->current_flow->args, ctl->current_flow->arg_count, str);
        sarg = search_insargs(ctl->current_flow->args, ctl->current_flow->arg_count, str);
        if (larg == NULL && sarg == NULL) {return result;}
        arg = (sarg == NULL) ? larg : sarg;
        result.mt = (arg->type == BOOL) ? DEPEN_FLAG : DEPEN_OPT;
        result.found = true;
        result.loc = arg;
        return result;
    }
    else {
        Arg *indep_arg, *larg, *sarg;
        Flow *flow;
        larg = search_inlargs(ctl->indep.args, ctl->indep.arg_count, str);
        sarg = search_insargs(ctl->indep.args, ctl->indep.arg_count, str);
        if (larg == NULL && sarg == NULL) {
            flow = search_inflows(ctl->flows, ctl->flow_count , str);
            if (flow == NULL) {return result;}
            result.mt = FLOW;
            result.found = true;
            result.loc =flow;
            return result;
        }
        else {
            indep_arg = (sarg == NULL) ? larg : sarg;
            result.mt = (indep_arg->type == BOOL) ? INDEP_FLAG : INDEP_OPT;
            result.found = true;
            result.loc = indep_arg;
            return result;
        }
    }

}

