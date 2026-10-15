/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:10:35 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 17:45:04 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

void	invalid_letters(char m)
{
	if (m != '0' && m != '1' && m != 'C' && m != 'E' && m != 'P')
	{
		ft_printf("Map Error\n");
		exit(1);
	}
}

void	rectangle(int *firstline, int *rowlen, int count)
{
	if (*firstline == 1)
	{
		*rowlen = count;
		*firstline = 0;
	}
	if (count != *rowlen)
	{
		ft_printf("Map error\n");
		exit(1);
	}
}

void	borders(int firstline, char *map, int i)
{
	if (firstline == 1 && map[i] != '1')
	{
		ft_printf("Map error\n");
		exit(1);
	}
	if (map[i] != '1' && map[i + 1] == '\n')
	{
		ft_printf("Map error\n");
		exit(1);
	}
}

void	mapform(char *map, int *charepeat, int *exrepeat, int *rowlen)
{
	int	firstline;
	int	i;
	int	count;

	firstline = 1;
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != '1' && map[i] != '\n')
		{
			ft_printf("Map error\n");
			exit(1);
		}
		count = 0;
		while (map[i] != '\n' && map[i] != '\0')
		{
			borders(firstline, map, i);
			double_letters(map, i, charepeat, exrepeat);
			count++;
			i++;
		}
		rectangle(&firstline, rowlen, count);
		if (map[i] != '\0')
			i++;
	}
}

void	valid_map(char *map, int nrows)
{
	int	rowlen;
	int	charepeat;
	int	exrepeat;

	exrepeat = 0;
	charepeat = 0;
	mapform(map, &charepeat, &exrepeat, &rowlen);
	valid_path(map, rowlen, nrows);
}
