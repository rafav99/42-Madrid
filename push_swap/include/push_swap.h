#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stddef.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
typedef struct s_stack
{
    int *v;
    int n;
    int cap;
} t_stack;
int parse_args(int argc, char **argv, int **out);
int normalize(int *values, int n);
void op(t_stack *a, t_stack *b, const char *name);
void sort_small(t_stack *a, t_stack *b);
void sort_chunks(t_stack *a, t_stack *b);
int sorted(t_stack *a);
#endif
