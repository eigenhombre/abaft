#ifndef __BINDING_H__
#define __BINDING_H__

typedef enum {
    CONSTANT,
} binding_type;

typedef struct binding {
    char *name;
    binding_type type;
    union {
        int constant;
    } value;
    struct binding *prev;
} binding;

binding *new_binding(char *name, binding_type type, int value, binding *prev);
void free_bindings(binding *latest);
int lookup_binding(binding *latest, char *name, int *value);

#endif