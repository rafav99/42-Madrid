/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:28:24 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/23 19:32:10 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct t_vars
{
	void	*mlx;
	void	*mlxwin;		
	void	*mchar;
	void	*mchar2;
	void	*grass;
	void	*wall;
	void	*book;
	void	*exit;
	char	*map;
	int		rowlen;
	int		xpos;
	int		ypos;
	int		turn;
	int		moves;
}	t_vars;

void	m_left(t_vars *mlxv, int *finished);
void	m_right(t_vars *mlxv, int *finished);
void	m_up(t_vars *mlxv, int *finished);
void	m_down(t_vars *mlxv, int *finished);
void	loadstate(t_vars mlxv, char *map, int h, int v);
void	loadcharac(t_vars *mlxv, char *map, int *h, int *v);
void	loadwall(t_vars mlxv, char *map, int h, int v);
int		countbooks(char *map);
void	loadbooks(t_vars mlxv, char *map, int h, int v);
void	loadexit(t_vars mlxv, char *map, int h, int v);
void	loadfinexit(t_vars mlxv, char *map, int h, int v);
int		checkmap(t_vars mlxv, char *map, int key);
int		move(int key, t_vars *mlxv);
void	loadstate(t_vars mlxv, char *map, int h, int v);
void	loadwall(t_vars mlxv, char *map, int h, int v);
void	valid_path(char *map, int rowlen, int nrows);
void	render(char *map, int nrows, int len);
char	*get_next_line(int fd);
int		readmap(char *map, int nrows, int fd, char *a);
void	charpos(t_vars *mlxv, char *map);
void	invalid_letters(char m);
void	leftborder(int m);
void	valid_map(char *map, int nrows);
void	mapform(char *map, int *charepeat, int *exrepeat, int *rowlen);
void	rectangle(int *firstline, int *rowlen, int count);
void	flood_map(char *auxmap, int rowlen, int i, int *change);
void	flood_loop(char *auxmap, int rowlen, int nrows, int change);
int		comp_check(char *auxmap);
void	double_letters(char *map, int i, int *charepeat, int *exrepeat);

size_t	ft_strlen(const char *str);
void	image_error(void *image);

#endif