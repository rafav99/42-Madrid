#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#ifndef GNL_MAX_FD
# define GNL_MAX_FD 4096
#endif

static char *joined_free(char *a, const char *b)
{
    char *out;
    if (!a)
        a = ft_strdup("");
    if (!a)
        return (NULL);
    out = ft_strjoin(a, b);
    free(a);
    return (out);
}

static char *extract_line(char **saved)
{
    char *cut;
    char *line;
    char *remaining;
    size_t length;

    cut = ft_strchr(*saved, '\n');
    length = cut ? (size_t)(cut - *saved + 1) : ft_strlen(*saved);
    line = ft_substr(*saved, 0, length);
    if (!line)
        return (NULL);
    remaining = cut ? ft_strdup(*saved + length) : NULL;
    if (cut && !remaining)
    {
        free(line);
        return (NULL);
    }
    free(*saved);
    *saved = remaining;
    if (*saved && !**saved)
    {
        free(*saved);
        *saved = NULL;
    }
    return (line);
}

char *get_next_line(int fd)
{
    static char *saved[GNL_MAX_FD];
    char buffer[BUFFER_SIZE > 0 ? BUFFER_SIZE + 1 : 1];
    ssize_t count;
    char *next;

    if (fd < 0 || fd >= GNL_MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    while (!saved[fd] || !ft_strchr(saved[fd], '\n'))
    {
        count = read(fd, buffer, BUFFER_SIZE);
        if (count <= 0)
        {
            if (count < 0 || !saved[fd] || !*saved[fd])
            {
                free(saved[fd]);
                saved[fd] = NULL;
                return (NULL);
            }
            break ;
        }
        buffer[count] = 0;
        next = joined_free(saved[fd], buffer);
        saved[fd] = next;
        if (!next)
            return (NULL);
    }
    return (extract_line(&saved[fd]));
}
