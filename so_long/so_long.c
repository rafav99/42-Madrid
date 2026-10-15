/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:10:41 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 18:45:36 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

int	countbooks(char *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'C')
			count++;
		i++;
	}
	return (count);
}

void	charpos(t_vars *mlxv, char *map)
{
	int	i;
	int	verpos;
	int	horpos;

	verpos = 10;
	horpos = 10;
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'P')
		{
			mlxv->xpos = horpos;
			mlxv->ypos = verpos;
		}
		if (map[i] == '\n')
		{
			verpos = verpos + 64;
			horpos = 10;
		}
		else
			horpos = horpos + 64;
		i++;
	}
}

void	all_letters(char *map)
{
	int	l_c;
	int	l_p;
	int	l_e;
	int	i;

	i = 0;
	l_c = 0;
	l_p = 0;
	l_e = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'C')
			l_c = 1;
		if (map[i] == 'P')
			l_p = 1;
		if (map[i] == 'E')
			l_e = 1;
		i++;
	}
	if (l_c == 0 || l_p == 0 || l_e == 0)
	{
		ft_printf("Error\n");
		exit(2);
	}
}

static char *append_map(char *map, const char *line)
{
    char *combined;
    if (!map)
        return (ft_strdup(line));
    combined = ft_strjoin(map, line);
    free(map);
    return (combined);
}

int readmap(char *map, int nrows, int fd, char *a)
{
    int len;
    char *next;

    if (!a)
        return (1);
    len = (int)ft_strlen(a);
    while (a)
    {
        next = append_map(map, a);
        free(a);
        if (!next)
        {
            free(map);
            close(fd);
            return (1);
        }
        map = next;
        nrows++;
        a = get_next_line(fd);
    }
    close(fd);
    all_letters(map);
    valid_map(map, nrows);
    render(map, nrows, len);
    free(map);
    return (0);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*map;
	char	*a;
	int		nrows;

	if (argc != 2)
	{
		ft_printf("Error\n");
		exit(1);
	}
	map = NULL;
	nrows = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n");
		exit(1);
	}
	a = get_next_line(fd);
	if (a == NULL)
	{
		ft_printf("Error\n");
		exit(1);
	}
	readmap(map, nrows, fd, a);
}
