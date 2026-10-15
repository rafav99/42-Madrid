#include "push_swap.h"
#include "../../libft/libft.h"

static int digit(char c)
{
    return (c >= '0' && c <= '9');
}

static int number(const char **s, int *value)
{
    long n;
    int sign;

    n = 0;
    sign = 1;
    if (**s == '+' || **s == '-')
    {
        if (**s == '-')
            sign = -1;
        ++(*s);
    }
    if (!digit(**s))
        return (0);
    while (digit(**s))
    {
        if (n > 2147483648L / 10 || (n == 2147483648L / 10
                && (**s - '0') > 2147483648L % 10))
            return (0);
        n = n * 10 + (**s - '0');
        if (n > 2147483648L || (sign == 1 && n > INT_MAX))
            return (0);
        ++(*s);
    }
    *value = (int)(n * sign);
    if (**s && !ft_isspace((unsigned char)**s))
        return (0);
    return (1);
}

static int append(int **values, int *n, int *cap, int value)
{
    int *next;
    int i;

    if (*n == *cap)
    {
        next = malloc(sizeof(int) * (*cap * 2));
        if (!next)
            return (0);
        i = -1;
        while (++i < *n)
            next[i] = (*values)[i];
        free(*values);
        *values = next;
        *cap *= 2;
    }
    (*values)[(*n)++] = value;
    return (1);
}

int parse_args(int argc, char **argv, int **out)
{
    int i;
    int n;
    int cap;
    int value;
    const char *s;
    int ok;

    cap = 16;
    n = 0;
    ok = 1;
    *out = malloc(sizeof(int) * cap);
    if (!*out)
        return (-1);
    i = 0;
    while (++i < argc && ok)
    {
        s = argv[i];
        while (*s && ft_isspace((unsigned char)*s))
            ++s;
        if (!*s)
            ok = 0;
        while (*s && ok)
        {
            if (!number(&s, &value) || !append(out, &n, &cap, value))
                ok = 0;
            while (*s && ft_isspace((unsigned char)*s))
                ++s;
        }
    }
    if (!ok || !n)
    {
        free(*out);
        *out = NULL;
        return (-1);
    }
    return (n);
}
