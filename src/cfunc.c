#include <abaft/cfunc.h>
#include <abaft/types.h>
#include <stdio.h>   // printf
#include <stdlib.h>  // exit

#define CHECK_POP(s, v)                       \
    if (pop(s, &v) == EVAL_STACK_UNDERFLOW) { \
        return EVAL_STACK_UNDERFLOW;          \
    }

err_t add(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, a + b);
    return EVAL_OK;
}

err_t mul(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, a * b);
    return EVAL_OK;
}

err_t sub(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, b - a);
    return EVAL_OK;
}

err_t divide(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, b / a);
    return EVAL_OK;
}

err_t dot(stack *s) {
    selem a;
    CHECK_POP(s, a);
    printf("%d\n", a);
    return EVAL_OK;
}

err_t dup(stack *s) {
    selem a;
    CHECK_POP(s, a);
    push(s, a);
    push(s, a);
    return EVAL_OK;
}

err_t drop(stack *s) {
    selem a;
    CHECK_POP(s, a);
    return EVAL_OK;
}

err_t rot(stack *s) {
    selem a, b, c;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    CHECK_POP(s, c);
    push(s, b);
    push(s, a);
    push(s, c);
    return EVAL_OK;
}

err_t swap(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, a);
    push(s, b);
    return EVAL_OK;
}

err_t over(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, b);
    push(s, a);
    push(s, b);
    return EVAL_OK;
}

err_t equal(stack *s) {
    selem a, b;
    CHECK_POP(s, a);
    CHECK_POP(s, b);
    push(s, a == b ? -1 : 0);  // FIXME: define TRUE and FALSE
    return EVAL_OK;
}

err_t assert_(stack *s) {
    selem a;
    CHECK_POP(s, a);
    if (a == 0) {
        return EVAL_ASSERTION_FAILED;
    }
    return EVAL_OK;
}
