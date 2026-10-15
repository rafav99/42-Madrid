#include "push_swap.h"
#include "../../libft/libft.h"

static void rotate(t_stack *s, int reverse)
{
    int tmp;
    int i;

    if (s->n < 2)
        return ;
    if (reverse)
    {
        tmp = s->v[s->n - 1];
        i = s->n;
        while (--i > 0)
            s->v[i] = s->v[i - 1];
        s->v[0] = tmp;
    }
    else
    {
        tmp = s->v[0];
        i = -1;
        while (++i < s->n - 1)
            s->v[i] = s->v[i + 1];
        s->v[s->n - 1] = tmp;
    }
}

static void push(t_stack *from, t_stack *to)
{
    int i;

    if (!from->n)
        return ;
    i = to->n;
    while (i-- > 0)
        to->v[i + 1] = to->v[i];
    to->v[0] = from->v[0];
    ++to->n;
    --from->n;
    i = -1;
    while (++i < from->n)
        from->v[i] = from->v[i + 1];
}

static int eq(const char *a, const char *b)
{
    return (ft_strcmp(a, b) == 0);
}

void op(t_stack *a, t_stack *b, const char *name)
{
    int tmp;
    t_stack *s;

    s = a;
    if (name[1] == 'b' || (name[0] == 'r' && name[1] == 'b')
        || (name[0] == 'r' && name[1] == 'r' && name[2] == 'b'))
        s = b;
    if (eq(name, "pa"))
        push(b, a);
    else if (eq(name, "pb"))
        push(a, b);
    else if (eq(name, "sa") || eq(name, "sb"))
    {
        if (s->n >= 2)
        {
            tmp = s->v[0];
            s->v[0] = s->v[1];
            s->v[1] = tmp;
        }
    }
    else if (eq(name, "ra") || eq(name, "rb"))
        rotate(s, 0);
    else if (eq(name, "rra") || eq(name, "rrb"))
        rotate(s, 1);
    write(1, name, ft_strlen(name));
    write(1, "\n", 1);
}

int sorted(t_stack *a)
{
    int i;

    i = 0;
    while (++i < a->n)
        if (a->v[i - 1] > a->v[i])
            return (0);
    return (1);
}
