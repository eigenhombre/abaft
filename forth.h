#ifndef __FORTH_H__
#define __FORTH_H__

#include "stack.h"
#include "stdbool.h"

typedef struct entry {
    char *name;
    void (*func)(stack *s);
    int *def;
    int deflen;
    bool immediate;
} entry;

entry *lookup(char *name, int len);

typedef enum {
    INTERPRET_NORMAL = 0,
    INTERPRET_VERBOSE,
} eval_mode;

void eval_word(char *word, int len, stack *s);

void eval_line(char *line, stack *s, eval_mode mode);

void eval_file(const char *filename, stack *s);

#endif
