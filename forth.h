#ifndef __FORTH_H__
#define __FORTH_H__

#include "stack.h"

typedef struct entry {
    char *name;
    void (*func)(stack *s);
} entry;

entry *lookup(char *name);

typedef enum {
    INTERPRET_NORMAL = 0,
    INTERPRET_VERBOSE,
} interpret_mode;

void interpret_word(char *word, stack *s);

void interpret_line(char *line, stack *s, interpret_mode mode);

#endif