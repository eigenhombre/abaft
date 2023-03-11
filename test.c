#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binding.h"
#include "parse.h"
#include "stack.h"

void test_stack(void) {
    // round trip alloc/free:
    free_stack(new_stack(100));

    // push and pop, empty, full:
    stack *s = new_stack(1);
    assert(stack_empty(s));
    assert(!stack_full(s));
    assert(0 == stack_count(s));

    push(s, 42);
    assert(!stack_empty(s));
    assert(1 == stack_count(s));

    assert(42 == pop(s));
    assert(stack_empty(s));

    free_stack(s);
}

void test_parse_number(void) {
    int value;
    assert(parse_number("123", &value));
    assert(123 == value);
    assert(!parse_number("abc", &value));
    assert(!parse_number("", &value));
}

void test_binding(void) {
    binding *l = new_binding("foo", CONSTANT, 42, NULL);
    l = new_binding("bar", CONSTANT, 33, l);
    int lookup_val;
    assert(lookup_binding(l, "foo", &lookup_val));
    assert(42 == lookup_val);
    assert(lookup_binding(l, "bar", &lookup_val));
    assert(33 == lookup_val);
    assert(!lookup_binding(l, "glarch", &lookup_val));
    free_bindings(l);
}

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
    push(s, a - b);
}

void divide(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, a / b);
}

typedef struct entry {
    char *name;
    void (*func)(stack *s);
} entry;

enum {
    ADD,
    MUL,
    SUB,
    DIV,
    NUM_ENTRIES,
};

entry dict[] = {
    {"+", &add   },
    {"*", &mul   },
    {"-", &sub   },
    {"/", &divide},
};

entry *lookup(char *name) {
    for (int i = 0; i < NUM_ENTRIES; i++) {
        if (strcmp(dict[i].name, name) == 0) {
            return &dict[i];
        }
    }
    return NULL;
}

void test_example_word(void) {
    stack *s = new_stack(100);
    push(s, 1);
    push(s, 2);
    lookup("+")->func(s);
    assert(3 == pop(s));
    free_stack(s);
}

int main(void) {
    test_stack();
    test_parse_number();
    test_binding();
    test_example_word();
}
