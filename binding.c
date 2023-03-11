#include "binding.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

binding *new_binding(char *name, binding_type type, int value, binding *prev) {
    binding *b = malloc(sizeof(binding));
    b->name = name;
    b->type = type;
    b->value.constant = value;
    b->prev = prev;
    return b;
}

void free_bindings(binding *b) {
    if (b->prev) {
        free_bindings(b->prev);
    }
    free(b);
}

int lookup_binding(binding *b, char *name, int *value) {
    while (b) {
        if (strcmp(b->name, name) == 0) {
            *value = b->value.constant;
            return 1;
        }
        b = b->prev;
    }
    return 0;
}
