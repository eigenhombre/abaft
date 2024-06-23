#include "forth.h"

#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "cfunc.h"
#include "parse.h"
#include "stack.h"

int homegrown;
bool compile_mode = false;

// void semicolon(stack *s) {
//     compile_mode = false;
//     printf("Leaving compile mode\n");
//     homegrown++;
// }

int compile_index = 0;

int sq_as_ints[] = {5, 1};

#define MAX_WORDS 100

enum {
    PLUS,
    TIMES,
    MINUS,
    DIVIDE,
    DOT,
    DUP,
    DROP,
    ROT,
    SWAP,
    OVER,
    EQUAL,
    ASSERT,
    SQ,
    // SEMI,
    NUM_BUILTINS,
};

int homegrown = NUM_BUILTINS;

entry dict[MAX_WORDS] = {

    [PLUS] = {"+", &add},
    [TIMES] = {"*", &mul},
    [MINUS] = {"-", &sub},
    [DIVIDE] = {"/", &divide},
    [DOT] = {".", &dot},
    [DUP] = {"dup", &dup},
    [DROP] = {"drop", &drop},
    [ROT] = {"rot", &rot},
    [SWAP] = {"swap", &swap},
    [OVER] = {"over", &over},
    [EQUAL] = {"=", &equal},
    [ASSERT] = {"assert", &assert_},
    [SQ] = {"sq", NULL, sq_as_ints, 2},

    // [SEMI] = {";", &semicolon},
    //     {"+", &add},
    //     {"*", &mul},
    //     {"-", &sub},
    //     {"/", &divide},
    //     {".", &dot},
    //     {"dup", &dup},
    //     {"drop", &drop},
    //     {"rot", &rot},
    //     {"swap", &swap},
    //     {"over", &over},
    //  // Emulate a "user-defined" function:
    //     {"sq", NULL, sq_as_ints, 2},
    //  // {":", &colon},
    //     {";", &semicolon},
};

entry *lookup(char *name, int len) {
    for (int i = 0; i < sizeof(dict) / sizeof(entry); i++) {
        if (strncmp(dict[i].name, name, len) == 0) {
            return &dict[i];
        }
    }
    return NULL;
}

void print_stack(stack *s) {
    printf("Stack: ");
    for (int i = 0; i < stack_count(s); i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

void eval_word(char *line, int len, stack *s) {
    // Handle immediate word special cases:
    if (strncmp(line, ":", len) == 0) {
        compile_mode = true;
        printf("Entering compile mode\n");
        // get name of new word
        char *name = skip_whitespace(line + 1);
        char *end = name;
        int name_len = 0;
        while (*end && !isspace(*end)) {
            end++;
            name_len++;
        }
        printf("Name of new word is '%.*s'\n", name_len, name);
        dict[homegrown].name = name;
        dict[homegrown].def = malloc(100 * sizeof(int));
        dict[homegrown].deflen = 0;
        return;
    } else if (strncmp(line, ";", len) == 0) {
        compile_mode = false;
        printf("Leaving compile mode\n");
        homegrown++;
        return;
    }
    if (compile_mode) {
        entry *e = lookup(line, len);
        if (e) {
            dict[homegrown].def[dict[homegrown].deflen] = e - dict;
            dict[homegrown].deflen++;
            return;
        }
        int num;
        if (parse_number(line, len, &num)) {
            dict[homegrown].def[dict[homegrown].deflen] = num;
            dict[homegrown].deflen++;
            return;
        }
        printf("Unknown word in compile mode: '%.*s'\n", len, line);
    }
    // See if it's a number; if so, push it on the stack:
    int num;
    if (parse_number(line, len, &num)) {
        push(s, num);
        return;
    }
    // See if it's a word
    entry *e = lookup(line, len);
    if (e) {
        if (e->func) {
            // printf("Calling built in function %s\n", e->name);
            e->func(s);
        } else {  // It's an interpreted function:
            for (int i = 0; i < e->deflen; i++) {
                // printf("%d: %d (%s)\n", i, e->def[i],
                // dict[e->def[i]].name); print_stack(s);
                dict[e->def[i]].func(s);
            }
        }
        return;
    } else {
        printf("Unknown word at beginning of: '%s'\n", line);
    }
}

void eval_line(char *line, stack *s, eval_mode mode) {
    if (mode == INTERPRET_VERBOSE) {
        printf("> %s", line);
    }
    // TODO: handle overflow
    char *start = skip_whitespace(line);
    while (*start) {
        // TODO: handle overflow
        char *end = advance_token(start);
        int len = end - start;
        if (len == 0) {
            break;
        }
        eval_word(start, len, s);
        start = skip_whitespace(end);
    }
}

void eval_file(const char *filename, stack *s) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, f)) != -1) {
        // TODO: make printing optional:
        printf("%s", line);
        eval_line(line, s, INTERPRET_NORMAL);
    }
    free(line);
    fclose(f);
}
