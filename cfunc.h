#ifndef __CFUNC_H__
#define __CFUNC_H__

#include "stack.h"

void add(stack *s);
void mul(stack *s);
void sub(stack *s);
void divide(stack *s);
void dot(stack *s);
void dup(stack *s);
void drop(stack *s);
void rot(stack *s);
void swap(stack *s);
void over(stack *s);
void equal(stack *s);
void assert_(stack *s);

#endif
