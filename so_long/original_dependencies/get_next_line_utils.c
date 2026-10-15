/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:54:43 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/07 17:08:42 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"

void	ft_loop(char const *s, unsigned int start, size_t len, char *p)
{
	int	i;

	i = 0;
	while (i < (int)len && s[i] != '\0')
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;

	if (s == NULL)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
	{
		p = malloc(1);
		if (p == NULL)
			return (0);
		p[0] = '\0';
		return (p);
	}
	p = malloc(len + 1);
	if (p == NULL)
		return (0);
	ft_loop(s, start, len, p);
	return (p);
}

void	endstr(char *p, const char *s2, int i, int j)
{
	if (s2[j] == '\n')
	{
		p[i] = '\n';
		p[i + 1] = '\0';
	}
	else
		p[i] = '\0';
}

void	join_aux(char *s1, char const *s2, char *p)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	endstr(p, s2, i, j);
}

int	check_buff(char *buffer)
{
	int	i;

	i = 0;
	while (i < 1)
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
