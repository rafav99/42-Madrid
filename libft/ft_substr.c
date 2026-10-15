/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:04:23 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:04:25 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_loop(char const *s, unsigned int start, size_t len, char *p)
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
