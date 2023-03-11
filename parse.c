#include "parse.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int parse_number(char *line, int *value) {
    int number = 0;
    int i = 0;
    if (!strlen(line)) {
        return 0;
    }
    while (line[i] != 0) {
        if (isdigit(line[i])) {
            number = number * 10 + (line[i] - '0');
        } else {
            return 0;
        }
        i++;
    }
    *value = number;
    return 1;
}
