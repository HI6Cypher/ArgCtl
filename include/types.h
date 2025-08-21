#ifndef TYPES_H
#define TYPES_H

#define MAX_PROG_NAME_SIZE 256
#define MAX_FLOW_NAME_SIZE 16
#define MAX_TYPE_NAME_SIZE 32
#define MAX_LONG_ARG_SIZE 16
#define MAX_SHORT_ARG_SIZE 8

typedef enum {false, true} bool;

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
    bool bool_val;
    unsigned char *string_val;
    unsigned char *custom_val;
} Custom;

typedef struct {
    unsigned char larg[MAX_LONG_ARG_SIZE];
    unsigned char sarg[MAX_SHORT_ARG_SIZE];
    unsigned char tname[MAX_TYPE_NAME_SIZE];
    unsigned char *help;
    unsigned short larg_cksum;
    unsigned short sarg_cksum;
    unsigned int nval;
    Types type;
    bool (*check_type)(void *val);
    bool required;
    bool specified;
    Custom value;
    Custom default_val;
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
    Flow current_flow;
    unsigned char name[MAX_PROG_NAME_SIZE];
    unsigned char *help;
    unsigned int flow_count;
} ArgCtl;

typedef Arg Option;
typedef Arg Flag;

#endif
