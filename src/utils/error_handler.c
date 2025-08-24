#include "utils/error_handler.h"

void raise_global_error(const unsigned char *pos, const unsigned char *msg) {
    fprintf(stderr, GLOBAL_ERROR_MSG, msg, pos, __LINE__, __FILE__);
    exit(EXIT_FAILURE);
    return;
}

void raise_malloc_error(const unsigned char *pos, const unsigned char *reason) {
    fprintf(stderr, MALLOC_ERROR_MSG, pos, reason, errno, strerror(errno));
    exit(EXIT_FAILURE);
    return;
}

void raise_realloc_error(const unsigned char *pos, const unsigned char *reason) {
    fprintf(stderr, REALLOC_ERROR_MSG, pos, reason, errno, strerror(errno));
    exit(EXIT_FAILURE);
    return;
}

void raise_novalue_error(const unsigned char *arg_name) {
    fprintf(stderr, NOVALUE_ERROR_MSG, arg_name);
    exit(EXIT_FAILURE);
    return;
}


void raise_conflict_error(const unsigned char *f_larg, const unsigned char *f_sarg, const unsigned char *s_larg, const unsigned char *s_sarg) {
    fprintf(stderr, CONFLICT_ERROR_MSG, f_larg, f_sarg, s_larg, s_sarg);
    exit(EXIT_FAILURE);
    return;
}

void raise_invalid_type_error(const unsigned char *larg, const unsigned char *sarg, const unsigned char *tname) {
    fprintf(stderr, INVALID_TYPE_ERROR_MSG, larg, sarg, tname);
    exit(EXIT_FAILURE);
    return;
}

void raise_notfound_error(const unsigned char *arg_name) {
    fprintf(stderr, NOTFOUND_ERROR_MSG, arg_name);
    exit(EXIT_FAILURE);
    return;
}
