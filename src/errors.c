#include <abaft/types.h>

const char *err_strs[] = {
    [EVAL_OK] = "EVAL_OK",
    [EVAL_UNKNOWN_WORD] = "unknown word",
    [EVAL_UNKNOWN_FILE] = "file not found",
    [EVAL_STACK_UNDERFLOW] = "stack underflow",
    [EVAL_ASSERTION_FAILED] = "assertion failed",
};
