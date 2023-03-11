#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "forth.h"
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

void test_example_word(void) {
    stack *s = new_stack(100);
    push(s, 1);
    push(s, 2);
    lookup("+")->func(s);
    assert(3 == pop(s));
    free_stack(s);
}

void test_interpreter(void) {
    interpret_mode i_n = INTERPRET_NORMAL;
    stack *s = new_stack(100);
    interpret_word("1", s);
    interpret_word("2", s);
    interpret_word("+", s);
    assert(3 == pop(s));

    interpret_line("", s, i_n);
    interpret_line(" ", s, i_n);
    interpret_line("1", s, i_n);
    assert(1 == pop(s));
    interpret_line(" 1", s, i_n);
    assert(1 == pop(s));
    interpret_line(" 1  ", s, i_n);
    assert(1 == pop(s));
    interpret_line("1 2 3", s, i_n);
    assert(3 == pop(s));
    assert(2 == pop(s));
    assert(1 == pop(s));
    interpret_line("1 2 +", s, i_n);
    assert(3 == pop(s));
    interpret_line("1 2 + 10 *", s, i_n);
    assert(30 == pop(s));
    free_stack(s);
}

int main(void) {
    test_stack();
    test_parse_number();
    test_example_word();
    test_interpreter();
}
