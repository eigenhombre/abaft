#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t selem;

typedef struct stack {
    selem *data;
    int size;
    int sp;
} stack;

typedef enum {
    INTERPRET_NORMAL = 0,
    INTERPRET_VERBOSE,
} eval_mode;

// See errors.c for descriptions:
typedef enum {
    EVAL_OK,
    EVAL_UNKNOWN_WORD,
    EVAL_UNKNOWN_FILE,
    EVAL_STACK_UNDERFLOW,
    EVAL_ASSERTION_FAILED,
    //
    EVAL_NUM_ERRORS,
} err_t;

extern const char *err_strs[];

typedef struct entry {
    char *name;
    err_t (*func)(stack *s);
    int *def;
    int deflen;
    bool immediate;
} entry;

entry *lookup(char *name, int len);

#endif