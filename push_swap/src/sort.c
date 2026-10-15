#include "push_swap.h"

static void smallest_to_top(t_stack *a, t_stack *b)
{
    int i;
    int pos;

    i = 0;
    pos = 0;
    while (++i < a->n)
        if (a->v[i] < a->v[pos])
            pos = i;
    if (pos <= a->n / 2)
        while (pos-- > 0)
            op(a, b, "ra");
    else
    {
        pos = a->n - pos;
        while (pos-- > 0)
            op(a, b, "rra");
    }
}

void sort_small(t_stack *a, t_stack *b)
{
    if (sorted(a))
        return ;
    if (a->n == 2)
    {
        op(a, b, "sa");
        return ;
    }
    while (a->n > 3)
    {
        smallest_to_top(a, b);
        op(a, b, "pb");
    }
    if (a->v[0] > a->v[1] && a->v[0] > a->v[2])
        op(a, b, "ra");
    else if (a->v[1] > a->v[0] && a->v[1] > a->v[2])
        op(a, b, "rra");
    if (a->v[0] > a->v[1])
        op(a, b, "sa");
    while (b->n)
        op(a, b, "pa");
}

static int nearest_chunk(t_stack *a, int upper)
{
    int front;
    int back;

    front = 0;
    back = a->n - 1;
    while (a->v[front] >= upper)
        ++front;
    while (a->v[back] >= upper)
        --back;
    if (front <= a->n - 1 - back)
        return (front);
    return (-(a->n - back));
}

static int max_pos(t_stack *b)
{
    int pos;
    int i;

    pos = 0;
    i = 0;
    while (++i < b->n)
        if (b->v[i] > b->v[pos])
            pos = i;
    return (pos);
}

void sort_chunks(t_stack *a, t_stack *b)
{
    int width;
    int upper;
    int step;
    int pos;

    width = 20;
    if (a->n > 100)
        width = 60;
    upper = width;
    while (a->n)
    {
        while (a->n && a->v[0] >= upper)
        {
            pos = nearest_chunk(a, upper);
            if (pos >= 0)
                while (pos-- > 0)
                    op(a, b, "ra");
            else
                while (pos++ < 0)
                    op(a, b, "rra");
        }
        op(a, b, "pb");
        if (b->n > 1 && b->v[0] < upper - width / 2)
            op(a, b, "rb");
        step = a->n + b->n;
        if (b->n == upper && upper < step)
            upper += width;
        if (upper > step)
            upper = step;
    }
    while (b->n)
    {
        pos = max_pos(b);
        if (pos <= b->n / 2)
            while (pos-- > 0)
                op(a, b, "rb");
        else
        {
            pos = b->n - pos;
            while (pos-- > 0)
                op(a, b, "rrb");
        }
        op(a, b, "pa");
    }
}
