#include "forth.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"
#include "stack.h"

void add(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, a + b);
}

void mul(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, a * b);
}

void sub(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, b - a);
}

void divide(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, b / a);
}

void dot(stack *s) {
    int a = pop(s);
    printf("%d\n", a);
}

void dup(stack *s) {
    int a = pop(s);
    push(s, a);
    push(s, a);
}

void drop(stack *s) { pop(s); }

void rot(stack *s) {
    int a = pop(s);
    int b = pop(s);
    int c = pop(s);
    push(s, b);
    push(s, a);
    push(s, c);
}

void swap(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, a);
    push(s, b);
}

void over(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, b);
    push(s, a);
    push(s, b);
}

entry dict[] = {
    {"+",    &add   },
    {"*",    &mul   },
    {"-",    &sub   },
    {"/",    &divide},
    {".",    &dot   },
    {"dup",  &dup   },
    {"drop", &drop  },
    {"rot",  &rot   },
    {"swap", &swap  },
    {"over", &over  },
};

entry *lookup(char *name) {
    for (int i = 0; i < sizeof(dict) / sizeof(entry); i++) {
        if (strcmp(dict[i].name, name) == 0) {
            return &dict[i];
        }
    }
    return NULL;
}

void interpret_word(char *word, stack *s) {
    // See if it's a number
    int num;
    if (parse_number(word, &num)) {
        push(s, num);
        return;
    }
    // See if it's a word
    entry *e = lookup(word);
    if (e) {
        e->func(s);
        return;
    }
}

void interpret_line(char *line, stack *s, interpret_mode mode) {
    if (mode == INTERPRET_VERBOSE) {
        printf("> %s", line);
    }
    char *start = skip_whitespace(line);
    while (*start) {
        char *end = advance_token(start);
        int len = end - start;
        if (len == 0) {
            break;
        }
        char *word = malloc(len + 1);
        strncpy(word, start, len);
        word[len] = '\0';
        interpret_word(word, s);
        free(word);
        start = skip_whitespace(end);
    }
}
