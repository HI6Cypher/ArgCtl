#include "utils/typecheck.h"

struct typecheck_t typecheck_integer(void *val) {
    struct typecheck_t result;
    char **endptr;
    long converted = strtol((unsigned char *) val, endptr, 0);
    if ((**endptr == '\0') && (errno != ERANGE && errno != EINVAL))
        result.isvalid = true;
        result.integer_val = converted;
    return result;
}

struct typecheck_t check_float_type(void *val) {
    struct typecheck_t result;
    char **endptr;
    float converted = strtof((unsigned char *) val, endptr);
    if ((**endptr == '\0') && (errno != ERANGE))
        result.isvalid = true;
        result.float_val = converted;
    return result;
}
