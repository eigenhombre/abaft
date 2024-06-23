#include <abaft/forth.h>
#include <abaft/parse.h>
#include <abaft/stack.h>
#include <abaft/types.h>
#include <assert.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    selem result;
    assert(EVAL_OK == pop(s, &result));
    assert(42 == result);
    assert(stack_empty(s));

    free_stack(s);
}

void test_parse_number(void) {
    int value;
    assert(parse_number("123", 3, &value));
    assert(123 == value);
    assert(!parse_number("abc", 3, &value));
    assert(!parse_number("", 0, &value));
}

static void is_err(int expected, int result) {
    if (result != expected) {
        printf("Expected error %d, got %d\n", expected, result);
    }
    assert(result == expected);
}

#define ASSERT_OK(result) is_err(EVAL_OK, result);

#define CHECK_POP(s, v, val)     \
    is_err(EVAL_OK, pop(s, &v)); \
    assert(val == v);

void test_example_word(void) {
    stack *s = new_stack(100);
    push(s, 1);
    push(s, 2);
    lookup("+", 1)->func(s);
    selem result;
    CHECK_POP(s, result, 3);
    free_stack(s);
}

void test_interpreter(void) {
    eval_mode i_n = INTERPRET_NORMAL;
    stack *s = new_stack(100);
    // YOU ARE HERE
    is_err(EVAL_STACK_UNDERFLOW, eval_word(".", 1, s));
    ASSERT_OK(eval_word("1", 1, s));
    ASSERT_OK(eval_word("2", 1, s));
    ASSERT_OK(eval_word("+", 1, s));
    selem result;
    CHECK_POP(s, result, 3);

    ASSERT_OK(eval_line("", s, i_n));
    ASSERT_OK(eval_line(" ", s, i_n));
    ASSERT_OK(eval_line("1", s, i_n));
    CHECK_POP(s, result, 1);
    ASSERT_OK(eval_line(" 1", s, i_n));
    CHECK_POP(s, result, 1);
    ASSERT_OK(eval_line(" 1  ", s, i_n));
    CHECK_POP(s, result, 1);
    ASSERT_OK(eval_line("1 2 3", s, i_n));
    CHECK_POP(s, result, 3);
    CHECK_POP(s, result, 2);
    CHECK_POP(s, result, 1);
    ASSERT_OK(eval_line("1 2 +", s, i_n));
    // assert(3 == pop(s));
    CHECK_POP(s, result, 3);
    ASSERT_OK(eval_line("1 2 + 10 *", s, i_n));
    // assert(30 == pop(s));
    CHECK_POP(s, result, 30);

    // TMP: Try interpreted fn:
    ASSERT_OK(eval_line("4 sq", s, i_n));
    CHECK_POP(s, result, 16);

    ASSERT_OK(eval_line(": square dup * ;", s, i_n));
    // YOU ARE HERE:
    // eval_line("4 square", s, i_n);
    free_stack(s);
}

void test_forth_tests(const char *filename) {
    stack *s = new_stack(100);
    eval_file(filename, s);
    free_stack(s);
}

int main(void) {
    test_stack();
    test_parse_number();
    test_example_word();
    test_interpreter();
    test_forth_tests("./tests.fs");
    printf("OK\n");
}
