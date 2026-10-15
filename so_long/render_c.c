/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:34:04 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 19:42:06 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include "so_long.h"

void	grassquare(t_vars mlxv, int hp, int vp)
{
	int	t;
	int	r;
	int	hs;
	int	vs;

	r = 0;
	while (r < 4)
	{
		t = 0;
		while (t < 4)
		{
			hs = hp + 16 * r;
			vs = vp + 16 * t;
			mlx_put_image_to_window(mlxv.mlx, mlxv.mlxwin, mlxv.grass, hs, vs);
			t++;
		}
		r++;
	}
}

void	loadstate(t_vars mlxv, char *map, int h, int v)
{
	int	i;
	int	hp;
	int	vp;

	vp = 0;
	hp = 0;
	mlxv.grass = mlx_xpm_file_to_image(mlxv.mlx, "imgs/wooden.xpm", &h, &v);
	image_error(mlxv.grass);
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '0' || map[i] == 'C' || map[i] == 'P' || map[i] == 'E')
			grassquare(mlxv, hp, vp);
		if (map[i] == '\n')
		{
			vp = vp + v * 4;
			hp = 0;
		}
		else
			hp = hp + h * 4;
		i++;
	}
}

int	end(void)
{
	exit(1);
}

void	setvars(t_vars *mlxv, int len, char *map)
{
	mlxv->rowlen = len;
	mlxv->ypos = 10;
	mlxv->xpos = 10;
	mlxv->turn = 1;
	mlxv->map = map;
}

static int linux_key_hook(int key, void *param)
{
    t_vars *vars;

    vars = (t_vars *)param;
    if (key == 65307)
        return (move(53, vars));
    if (key == 97 || key == 65361)
        return (move(0, vars));
    if (key == 100 || key == 65363)
        return (move(2, vars));
    if (key == 119 || key == 65362)
        return (move(13, vars));
    if (key == 115 || key == 65364)
        return (move(1, vars));
    return (0);
}

void	render(char *map, int nrows, int len)
{
	int		h;
	int		v;
	int		hz;
	t_vars	mlxv;

	mlxv.moves = 0;
	setvars(&mlxv, len, map);
	h = 0;
	v = 0;
	mlxv.mlx = mlx_init();
	charpos(&mlxv, map);
	hz = 64 * (len - 1);
	mlxv.mlxwin = mlx_new_window(mlxv.mlx, hz, 64 * nrows, "The library");
	loadstate(mlxv, map, h, v);
	loadwall(mlxv, map, 50, 50);
	loadbooks(mlxv, map, 20, 20);
	loadexit(mlxv, map, 20, 20);
	mlxv.mchar2 = mlx_xpm_file_to_image(mlxv.mlx, "imgs/bugrev.xpm", &h, &v);
	image_error(mlxv.mchar2);
	loadcharac(&mlxv, map, &h, &v);
	mlx_key_hook(mlxv.mlxwin, linux_key_hook, &mlxv);
	mlx_hook(mlxv.mlxwin, 17, 0, end, &mlxv);
	mlx_loop(mlxv.mlx);
}
