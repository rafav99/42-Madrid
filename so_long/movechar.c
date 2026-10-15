/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movechar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:52:58 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 19:58:09 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

void	vermove(int key, t_vars *mlxv, int *finished)
{
	if (key == 1 && checkmap(*mlxv, mlxv->map, 1) != 0)
	{
		m_up(mlxv, finished);
		mlxv->moves = mlxv->moves + 1;
		ft_printf("Moves: %i\n", mlxv->moves);
	}
	if (key == 13 && checkmap(*mlxv, mlxv->map, 13) != 0)
	{
		m_down(mlxv, finished);
		mlxv->moves = mlxv->moves + 1;
		ft_printf("Moves: %i\n", mlxv->moves);
	}
}

int	move(int key, t_vars *mlxv)
{
	int	finished;

	finished = 0;
#ifdef __linux__
    if (key == 97 || key == 65361) key = 0;
    else if (key == 100 || key == 65363) key = 2;
    else if (key == 119 || key == 65362) key = 13;
    else if (key == 115 || key == 65364) key = 1;
    else if (key == 65307) key = 53;
#endif
	if (key == 53)
		exit(1);
	if (key == 0 && checkmap(*mlxv, mlxv->map, 0) != 0)
	{
		m_left(mlxv, &finished);
		mlxv->moves = mlxv->moves + 1;
		ft_printf("Moves: %i\n", mlxv->moves);
	}
	if (key == 2 && checkmap(*mlxv, mlxv->map, 2) != 0)
	{
		m_right(mlxv, &finished);
		mlxv->moves = mlxv->moves + 1;
		ft_printf("Moves: %i\n", mlxv->moves);
	}
	vermove(key, mlxv, &finished);
	if (finished == 1)
		exit (1);
	return (0);
}

void	loadcharac(t_vars *mlxv, char *map, int *h, int *v)
{
	int	i;
	int	vp;
	int	hp;

	vp = 10;
	hp = 10;
	i = 0;
	mlxv->mchar = mlx_xpm_file_to_image(mlxv->mlx, "imgs/bug.xpm", h, v);
	image_error(mlxv->mchar);
	while (map[i] != '\0')
	{
		if (map[i] == 'P')
			mlx_put_image_to_window(mlxv->mlx, mlxv->mlxwin,
				mlxv->mchar, hp, vp);
		if (map[i] == '\n')
		{
			vp = vp + 64;
			hp = 10;
		}
		else
			hp = hp + 64;
		i++;
	}
}
