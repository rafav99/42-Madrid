/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_m.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:34:00 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 19:57:44 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

void	image_error(void *image)
{
	if (!image)
	{
		ft_printf("Error\n");
		exit(2);
	}
}

void	loadwall(t_vars mlxv, char *map, int h, int v)
{
	int	i;
	int	vp;
	int	hp;

	vp = 0;
	hp = 0;
	mlxv.wall = mlx_xpm_file_to_image(mlxv.mlx, "imgs/finshelf.xpm", &h, &v);
	image_error(mlxv.wall);
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '1')
			mlx_put_image_to_window(mlxv.mlx, mlxv.mlxwin, mlxv.wall, hp, vp);
		if (map[i] == '\n')
		{
			vp = vp + 64 ;
			hp = 0;
		}
		else
			hp = hp + 64;
		i++;
	}
}

void	loadfinexit(t_vars mlxv, char *map, int h, int v)
{
	int	i;
	int	vp;
	int	hp;

	vp = -10;
	hp = -15;
	mlxv.exit = mlx_xpm_file_to_image(mlxv.mlx, "imgs/exactive.xpm", &h, &v);
	image_error(mlxv.exit);
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'E')
			mlx_put_image_to_window(mlxv.mlx, mlxv.mlxwin, mlxv.exit, hp, vp);
		if (map[i] == '\n')
		{
			vp = vp + 64 ;
			hp = -15;
		}
		else
			hp = hp + 64;
		i++;
	}
}

void	loadbooks(t_vars mlxv, char *map, int h, int v)
{
	int	i;
	int	vp;
	int	hp;

	vp = 8;
	hp = 6;
	mlxv.book = mlx_xpm_file_to_image(mlxv.mlx, "imgs/book.xpm", &h, &v);
	image_error(mlxv.book);
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'C')
			mlx_put_image_to_window(mlxv.mlx, mlxv.mlxwin, mlxv.book, hp, vp);
		if (map[i] == '\n')
		{
			vp = vp + 64 ;
			hp = 6;
		}
		else
			hp = hp + 64;
		i++;
	}
}

void	loadexit(t_vars mlxv, char *map, int h, int v)
{
	int	i;
	int	vp;
	int	hp;

	vp = 2;
	hp = -25;
	mlxv.exit = mlx_xpm_file_to_image(mlxv.mlx, "imgs/blackexit.xpm", &h, &v);
	image_error(mlxv.exit);
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'E')
			mlx_put_image_to_window(mlxv.mlx, mlxv.mlxwin, mlxv.exit, hp, vp);
		if (map[i] == '\n')
		{
			vp = vp + 64 ;
			hp = -25;
		}
		else
			hp = hp + 64;
		i++;
	}
}
