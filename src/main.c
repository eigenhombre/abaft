#include <abaft/forth.h>
#include <abaft/names.h>
#include <abaft/parse.h>
#include <abaft/stack.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// choose random name from file
char *choose_name() {
    // select a random name from names array
    int num_names = sizeof(names) / sizeof(char *);
    int index = rand() % num_names;
    return names[index];
}

#define LINELEN 100

int main(int argc, char *argv[]) {
    srand(time(NULL));

    int stack_size = 10;
    stack *s = new_stack(stack_size);

    char *name = choose_name();
    printf("Sally Forth. %s Abaft.\n", name);

    // look for '-e' verbose interpret option:
    if (argc > 1 && strcmp(argv[1], "-e") == 0) {
        // read in the file and interpret it
        FILE *fp = fopen(argv[2], "r");
        if (fp == NULL) {
            printf("Unable to open file %s\n", argv[2]);
            return 1;
        }
        char line[LINELEN];
        while (fgets(line, LINELEN, fp) != NULL) {
            err_t result = eval_line(line, s, INTERPRET_VERBOSE);
            if (result != EVAL_OK) {
                printf("Error '%d (%s)' interpreting line: %s\n", result,
                       err_strs[result], line);
                return 1;
            }
        }
        return 0;
    }

    while (1) {
        printf("> ");
        // Read a line
        char line[LINELEN];
        char *lres = fgets(line, LINELEN, stdin);
        if (lres == NULL) {
            printf("EOF.  Bye!\n");
            break;
        }
        err_t result = eval_line(line, s, INTERPRET_NORMAL);
        if (result != EVAL_OK) {
            printf("Error '%d (%s)' interpreting line: %s\n", result,
                   err_strs[result], line);
        }
    }
    free(s);
    return 0;
}
