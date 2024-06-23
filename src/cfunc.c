#include <abaft/cfunc.h>
#include <stdio.h>   // printf
#include <stdlib.h>  // exit

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
    push(s, b - a);
}

void divide(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, b / a);
}

void dot(stack *s) {
    int a = pop(s);
    printf("%d\n", a);
}

void dup(stack *s) {
    int a = pop(s);
    push(s, a);
    push(s, a);
}

void drop(stack *s) { pop(s); }

void rot(stack *s) {
    int a = pop(s);
    int b = pop(s);
    int c = pop(s);
    push(s, b);
    push(s, a);
    push(s, c);
}

void swap(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, a);
    push(s, b);
}

void over(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, b);
    push(s, a);
    push(s, b);
}

void equal(stack *s) {
    int a = pop(s);
    int b = pop(s);
    push(s, a == b ? -1 : 0);  // FIXME: define TRUE and FALSE
}

void assert_(stack *s) {
    int a = pop(s);
    if (a == 0) {
        printf("Assertion failed\n");
        exit(-1);
    }
}
