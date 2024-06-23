#ifndef __FORTH_H__
#define __FORTH_H__

#include <abaft/stack.h>  // stack
#include <abaft/types.h>  // err_t

entry *lookup(char *name, int len);

err_t eval_word(char *word, int len, stack *s);

err_t eval_line(char *line, stack *s, eval_mode mode);

err_t eval_file(const char *filename, stack *s);

#endif
