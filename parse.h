#ifndef __PARSE_H__
#define __PARSE_H__

int parse_number(char *str, int len, int *num);

typedef enum {
    NUMBER,
    WORD,
} token_type;

typedef struct token {
    int type;
    union {
        int number;
        char *text;
    } u;
} token;

char *skip_whitespace(char *line);
char *advance_token(char *line);

#endif
