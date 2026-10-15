/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:07:22 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:07:24 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkstart(char const *s1, char const *set)
{
	int	i;
	int	c;
	int	check;

	check = 1;
	i = 0;
	while (i < (int)ft_strlen(s1) && check == 1)
	{
		c = 0;
		check = 0;
		while (c < (int)ft_strlen(set))
		{
			if (s1[i] == set[c])
				check = 1;
			c++;
		}
		i++;
	}
	if (check == 0)
		return (i - 1);
	else
		return ((int)ft_strlen(s1));
}

static int	ft_checkfinish(char const *s1, char const *set)
{
	int	i;
	int	c;
	int	check;

	check = 1;
	i = (int)ft_strlen(s1) - 1;
	while (i > 0 && check == 1)
	{
		c = 0;
		check = 0;
		while (c < (int)ft_strlen(set))
		{
			if (s1[i] == set[c])
				check = 1;
			c++;
		}
		i--;
	}
	if (check == 0)
		return (i + 1);
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	int		start;
	int		len;

	if (s1 == 0 || set == 0)
		return (0);
	start = ft_checkstart(s1, set);
	len = ft_checkfinish(s1, set) - start;
	p = ft_substr(s1, start, len + 1);
	return (p);
}
