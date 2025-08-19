#ifndef TYPES_H
#define TYPES_H

#define MAX_FLOW_NAME_SIZE 16
#define MAX_TYPE_NAME_SIZE 16
#define MAX_LONG_ARG_SIZE 16
#define MAX_SHORT_ARG_SIZE 8

typedef enum {FALSE, TRUE} Bool;

typedef enum {
    INTEGER,
    FLOAT,
    BOOL,
    STRING,
    CUSTOM,
} Types;

typedef union {
    signed long integer_val;
    float float_val;
    Bool bool_val;
    unsigned char *string_val;
    unsigned char *custome_val;
} Custom;

typedef struct {
    unsigned char larg[MAX_LONG_ARG_SIZE];
    unsigned char sarg[MAX_SHORT_ARG_SIZE];
    unsigned char *help;
    unsigned short larg_cksum;
    unsigned short sarg_cksum;
    unsigned int nargs;
    Types type;
    Bool (*check_type)(void *val);
    Bool required;
    Bool specified;
    Custome value;
    Custome default_val;
} Arg;

typedef struct {
    unsigned char name[MAX_FLOW_NAME_SIZE];
    unsigned char *help;
    unsigned short cksum;
    unsigned int req_count;
    unsigned int arg_count;
    Arg *args;
} Flow;

typedef struct {
    Flow *flows;
    Flow indep;
    Flow main;
    unsigned char *help;
    unsigned int flow_count;
} ArgCtl;

typedef Arg Option;
typedef Arg Flag;

#endif
