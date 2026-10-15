#include "push_swap.h"

static void quicksort(int *v, int lo, int hi)
{
    int i;
    int j;
    int pivot;
    int tmp;

    i = lo;
    j = hi;
    pivot = v[lo + (hi - lo) / 2];
    while (i <= j)
    {
        while (v[i] < pivot)
            ++i;
        while (v[j] > pivot)
            --j;
        if (i <= j)
        {
            tmp = v[i];
            v[i++] = v[j];
            v[j--] = tmp;
        }
    }
    if (lo < j)
        quicksort(v, lo, j);
    if (i < hi)
        quicksort(v, i, hi);
}

static int rank_of(int *ordered, int n, int val)
{
    int lo;
    int hi;
    int mid;

    lo = 0;
    hi = n - 1;
    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;
        if (ordered[mid] == val)
            return (mid);
        if (ordered[mid] < val)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return (-1);
}

int normalize(int *values, int n)
{
    int *copy;
    int i;

    copy = malloc(sizeof(int) * n);
    if (!copy)
        return (0);
    i = -1;
    while (++i < n)
        copy[i] = values[i];
    quicksort(copy, 0, n - 1);
    i = 0;
    while (++i < n)
    {
        if (copy[i] == copy[i - 1])
        {
            free(copy);
            return (0);
        }
    }
    i = -1;
    while (++i < n)
        values[i] = rank_of(copy, n, values[i]);
    free(copy);
    return (1);
}
