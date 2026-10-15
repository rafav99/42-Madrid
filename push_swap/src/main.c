#include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack a;
    t_stack b;
    int *values;
    int n;

    if (argc == 1)
        return (0);
    n = parse_args(argc, argv, &values);
    if (n < 0)
        return (write(2, "Error\n", 6), 1);
    if (!normalize(values, n))
        return (free(values), write(2, "Error\n", 6), 1);
    a.v = values;
    a.n = n;
    a.cap = n;
    b.v = malloc(sizeof(int) * n);
    if (!b.v)
        return (free(values), write(2, "Error\n", 6), 1);
    b.n = 0;
    b.cap = n;
    if (!sorted(&a))
    {
        if (n <= 5)
            sort_small(&a, &b);
        else
            sort_chunks(&a, &b);
    }
    free(a.v);
    free(b.v);
    return (0);
}
