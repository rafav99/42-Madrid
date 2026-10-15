/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:03:25 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 18:37:46 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

int	comp_check(char *auxmap)
{
	int	i;

	i = 0;
	while (auxmap[i] != '\0')
	{
		if (auxmap[i] == 'P' || auxmap[i] == 'C' || auxmap[i] == 'E' )
			return (0);
		i++;
	}
	return (1);
}

void	flood_map(char *auxmap, int rowlen, int i, int *change)
{
	if (auxmap[i + 1] != '\n' && auxmap[i + 1] != '1' && auxmap[i + 1] != 'A')
	{
		*change = 1;
		auxmap[i + 1] = 'A';
	}
	if (auxmap[i - 1] != '\n' && auxmap[i - 1] != '1' && auxmap[i - 1] != 'A')
	{
		*change = 1;
		auxmap[i - 1] = 'A';
	}
	if (i > rowlen && auxmap[i - rowlen - 1] != '\n')
	{
		if (auxmap[i - rowlen - 1] != '1' && auxmap[i - rowlen - 1] != 'A')
		{
			*change = 1;
			auxmap[i - rowlen - 1] = 'A';
		}
	}
}

void	flood_loop(char *ap, int rowlen, int nrows, int change)
{
	int	i;

	while (1)
	{
		i = 0;
		change = 0;
		while (ap[i] != '\0')
		{
			if (ap[i] == 'A' || ap[i] == 'P')
			{
				flood_map(ap, rowlen, i, &change);
				if (i < rowlen * nrows && ap[i + rowlen] != '\n')
				{
					if (ap[i + rowlen + 1] != '1' && ap[i + rowlen + 1] != 'A')
					{
						change = 1;
						ap[i + rowlen + 1] = 'A';
					}
				}
			}
			i++;
		}
		if (change == 0)
			break ;
	}
}

void	double_letters(char *map, int i, int *charepeat, int *exrepeat)
{
	invalid_letters(map[i]);
	if (map[i] == 'P')
	{
		if (*charepeat == 0)
			*charepeat = 1;
		else
		{
			ft_printf("Error: more than one character in map\n");
			exit(1);
		}
	}
	if (map[i] == 'E')
	{
		if (*exrepeat == 0)
			*exrepeat = 1;
		else
		{
			ft_printf("Error: more than one exit in map\n");
			exit(1);
		}
	}
}

void	valid_path(char *map, int rowlen, int nrows)
{
	int		i;
	char	*auxmap;
	int		change;

	change = 0;
	i = 0;
	auxmap = malloc(ft_strlen(map) + 1);
	while (map[i] != '\0')
	{
		auxmap[i] = map[i];
		if (map[i] != '1' && i > (rowlen + 1) * (nrows - 1) && map[i] != '\n')
		{
			ft_printf("Map error\n");
			exit(1);
		}
		i++;
	}
	auxmap[i] = '\0';
	flood_loop(auxmap, rowlen, nrows, change);
	if (comp_check(auxmap) == 0)
	{
		ft_printf("Error: no path found\n");
		exit(1);
	}
	free(auxmap);
}
