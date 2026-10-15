/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:53:11 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/07 14:06:59 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*p;

	if (s1 == NULL)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (s2 == NULL)
		return (0);
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (0);
	join_aux(s1, s2, p);
	if (s1 != NULL)
		free((void *)s1);
	return (p);
}

void	before(char *str, char **alline, char **save)
{
	int		i;
	char	*new_string;

	new_string = malloc(1 + 1);
	if (!new_string)
		return ;
	i = 0;
	while (str[i] != '\n')
	{
		new_string[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		new_string[i] = str[i];
	if (str[i + 1] != '\0')
		*save = ft_substr(str, i + 1, ft_strlen(&str[i]));
	if (str[i + 1] == '\0' && save != NULL)
	{
		free(*save);
		*save = NULL;
	}
	new_string[i + 1] = '\0';
	*alline = ft_strjoin(*alline, new_string);
	free(new_string);
	new_string = NULL;
}

char	*read_line(char *alline, char **save, int fd)
{
	char	*buffer;
	int		i;

	while (1)
	{
		buffer = malloc(1 + 1);
		if (!buffer)
			return (NULL);
		i = read(fd, buffer, 1);
		if (i <= 0)
		{
			free(buffer);
			break ;
		}
		buffer[i] = '\0';
		if (check_buff(buffer) >= 0)
		{
			before(buffer, &alline, save);
			free(buffer);
			return (alline);
		}
		alline = ft_strjoin(alline, buffer);
		free(buffer);
	}
	return (alline);
}

void	savelong(char **save)
{
	char		*aux;
	int			i;

	aux = *save;
	i = check_buff(*save);
	*save = ft_substr(*save, i + 1, ft_strlen(*save) - i + 1);
	free(aux);
	if (ft_strlen(*save) == 0)
	{
		free(*save);
		*save = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		*alline;
	static char	*save[4096];

	if (fd < 0 || 1 <= 0 || fd >= 4096)
		return (NULL);
	alline = NULL;
	if (save[fd] != NULL)
	{
		alline = ft_strjoin(alline, save[fd]);
		if (check_buff(save[fd]) >= 0 && save[fd][1] != '\0')
		{
			savelong(&save[fd]);
			return (alline);
		}
		free(save[fd]);
		save[fd] = NULL;
	}
	return (read_line(alline, &save[fd], fd));
}
