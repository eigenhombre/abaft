#include <abaft/parse.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int parse_number(char *line, int len, int *value) {
    int number = 0;
    int i = 0;
    if (len == 0) {
        return 0;
    }
    while (line[i] != 0 && i < len) {
        if (isdigit(line[i])) {
            number = number * 10 + (line[i] - '0');
        } else {
            return 0;
        }
        i++;
    }
    *value = number;
    return true;
}

// FIXME: handle overflow
char *skip_whitespace(char *line) {
    while (*line && isspace(*line)) {
        line++;
    }
    return line;
}

// FIXME: handle overflow
char *advance_token(char *line) {
    // Assumes no whitespace at beginning of line
    while (*line && !isspace(*line)) {
        line++;
    }
    return line;
}
