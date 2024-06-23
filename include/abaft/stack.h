#ifndef __STACK_H__
#define __STACK_H__

#include <abaft/types.h>
#include <stddef.h>
#include <stdint.h>

err_t pop(stack *s, selem *result);
void push(stack *s, selem el);
stack *new_stack(size_t size);
void free_stack(stack *s);
int stack_count(stack *s);
int stack_empty(stack *s);
int stack_full(stack *s);

void dbg_print_stack(stack *s);

#endif