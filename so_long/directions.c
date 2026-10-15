/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:20:18 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 18:50:34 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

void	m_left(t_vars *mlxv, int *finished)
{
	if (checkmap(*mlxv, mlxv->map, 0) == 2)
			*finished = 1;
	mlx_clear_window(mlxv->mlx, mlxv->mlxwin);
	loadstate(*mlxv, mlxv->map, 16, 16);
	loadwall(*mlxv, mlxv->map, 16, 16);
	loadbooks(*mlxv, mlxv->map, 0, 0);
	if (countbooks(mlxv->map) == 0)
		loadfinexit(*mlxv, mlxv->map, 0, 0);
	else
		loadexit(*mlxv, mlxv->map, 20, 20);
	mlxv->xpos = mlxv->xpos - 64;
	mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
		mlxv->mchar2, mlxv->xpos, mlxv->ypos);
	mlxv->turn = -1;
}

void	m_right(t_vars *mlxv, int *finished)
{
	if (checkmap(*mlxv, mlxv->map, 2) == 2)
			*finished = 1;
	mlx_clear_window(mlxv->mlx, mlxv->mlxwin);
	loadstate(*mlxv, mlxv->map, 16, 16);
	loadwall(*mlxv, mlxv->map, 16, 16);
	loadbooks(*mlxv, mlxv->map, 0, 0);
	if (countbooks(mlxv->map) == 0)
		loadfinexit(*mlxv, mlxv->map, 0, 0);
	else
		loadexit(*mlxv, mlxv->map, 20, 20);
	mlxv->xpos = mlxv->xpos + 64;
	mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
		mlxv->mchar, mlxv->xpos, mlxv->ypos);
	mlxv->turn = 1;
}

void	m_up(t_vars *mlxv, int *finished)
{
	if (checkmap(*mlxv, mlxv->map, 1) == 2)
		*finished = 1;
	mlx_clear_window(mlxv->mlx, mlxv->mlxwin);
	loadstate(*mlxv, mlxv->map, 16, 16);
	loadwall(*mlxv, mlxv->map, 16, 16);
	loadbooks(*mlxv, mlxv->map, 0, 0);
	if (countbooks(mlxv->map) == 0)
		loadfinexit(*mlxv, mlxv->map, 0, 0);
	else
		loadexit(*mlxv, mlxv->map, 20, 20);
	mlxv->ypos = mlxv->ypos + 64;
	if (mlxv->turn == 1)
		mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
			mlxv->mchar, mlxv->xpos, mlxv->ypos);
	else
		mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
			mlxv->mchar2, mlxv->xpos, mlxv->ypos);
}

void	m_down(t_vars *mlxv, int *finished)
{
	if (checkmap(*mlxv, mlxv->map, 13) == 2)
		*finished = 1;
	mlx_clear_window(mlxv->mlx, mlxv->mlxwin);
	loadstate(*mlxv, mlxv->map, 16, 16);
	loadwall(*mlxv, mlxv->map, 16, 16);
	loadbooks(*mlxv, mlxv->map, 0, 0);
	if (countbooks(mlxv->map) == 0)
		loadfinexit(*mlxv, mlxv->map, 0, 0);
	else
		loadexit(*mlxv, mlxv->map, 20, 20);
	mlxv->ypos = mlxv->ypos - 64;
	if (mlxv->turn == 1)
		mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
			mlxv->mchar, mlxv->xpos, mlxv->ypos);
	else
		mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
			mlxv->mchar2, mlxv->xpos, mlxv->ypos);
}

int	checkmap(t_vars mlxv, char *map, int key)
{
	int	tile;

	if (key == 0)
		mlxv.xpos = mlxv.xpos - 64;
	if (key == 2)
		mlxv.xpos = mlxv.xpos + 64;
	if (key == 1)
		mlxv.ypos = mlxv.ypos + 64;
	if (key == 13)
		mlxv.ypos = mlxv.ypos - 64;
	tile = ((mlxv.xpos - 10) / 64);
	tile = tile + (mlxv.rowlen * (mlxv.ypos - 10) / 64);
	if (map[tile] == '1')
		return (0);
	if (map[tile] == 'C')
	{
		map[tile] = '0';
		return (1);
	}
	if (map[tile] == 'E')
	{
		if (countbooks(map) == 0)
			return (2);
	}
	return (1);
}
