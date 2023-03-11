#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "names.h"
#include "parse.h"
#include "stack.h"

char *names[];

typedef enum ThingTypeEnum { CONSTANT } ThingType;

typedef int (*Func2)(int, int);

typedef struct ThingStruct {
    ThingType type;
    char *name;
    union {
        int constant;
        Func2 func;
    } u;
} Thing;

// choose random name from file
char *choose_name() {
    // select a random name from names array
    int num_names = sizeof(names) / sizeof(char *);
    int index = rand() % num_names;
    return names[index];
}

#define LINELEN 100

int interpret(char *line, stack *s) {
    while (*line) {
        char word[LINELEN];
        int wi = 0;
        int num;
        while (isspace(*line)) {
            line++;
        }
        while (*line && !isspace(*line)) {
            if (wi < sizeof(word)) {
                word[wi++] = *line++;
            }
            line++;
        }
        word[wi] = 0;
        if (wi == 0) {
            continue;
        }
        if (strcmp(line, "quit") == 0) {
            return 1;
        }
        if (parse_number(word, &num)) {
            push(s, num);
            dbg_print_stack(s);
        } else {
            printf("Unknown word: %s\n", word);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int stack_size = 10;
    stack *s = new_stack(stack_size);

    char *name = choose_name();
    printf("Sally Forth. %s Abaft.\n", name);

    while (1) {
        printf("abaft> ");
        // Read a line
        char line[LINELEN];
        char *result = fgets(line, LINELEN, stdin);
        if (result == NULL) {
            printf("EOF.  Bye!\n");
            break;
        }
        interpret(line, s);
        printf("%s", line);
    }
    free(s);
    return 0;
}
