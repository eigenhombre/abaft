#include <abaft/stack.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

err_t pop(stack *s, selem *result) {
    if (s->sp == 0) {
        return EVAL_STACK_UNDERFLOW;
    }
    *result = s->data[--s->sp];
    return EVAL_OK;
}

void push(stack *s, selem value) { s->data[s->sp++] = value; }

int stack_count(stack *s) { return s->sp; }

stack *new_stack(size_t size) {
    stack *s = malloc(sizeof(stack));
    s->size = size;
    s->sp = 0;
    s->data = malloc(size * sizeof(selem));
    return s;
}

void free_stack(stack *s) {
    free(s->data);
    free(s);
}

int stack_empty(stack *s) { return s->sp == 0; }
int stack_full(stack *s) { return s->sp == s->size; }

void dbg_print_stack(stack *s) {
    printf("stack (%d items) ", s->sp);
    for (size_t i = 0; i < s->sp; i++) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}
