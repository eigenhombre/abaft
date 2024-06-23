#ifndef __CFUNC_H__
#define __CFUNC_H__

#include <abaft/stack.h>  // stack
#include <abaft/types.h>  // err_t

err_t add(stack *s);
err_t mul(stack *s);
err_t sub(stack *s);
err_t divide(stack *s);
err_t dot(stack *s);
err_t dup(stack *s);
err_t drop(stack *s);
err_t rot(stack *s);
err_t swap(stack *s);
err_t over(stack *s);
err_t equal(stack *s);
err_t assert_(stack *s);

#endif
