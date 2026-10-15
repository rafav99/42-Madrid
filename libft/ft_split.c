/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:08:28 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:08:30 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkmany(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s != c && *s != '\0')
				s++;
		}
		if (*s != '\0')
			s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**r;
	int		j;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	r = malloc((ft_checkmany(s, c) + 1) * 8);
	if (r == NULL)
		return (NULL);
	while (j < ft_checkmany(s, c) && i < (int)ft_strlen(s))
	{
		while ((int)((char *)ft_memchr(&s[i], c, ft_strlen(&s[i])) == &s[i]))
			i++;
		len = (int)((char *)ft_memchr(&s[i], c, ft_strlen(&s[i])) - &s[i]);
		if (ft_memchr(&s[i], c, ft_strlen(&s[i])) == 0)
			len = ft_strlen(&s[i]);
		r[j] = ft_substr(&s[i], 0, len);
		i = i + len + 1;
		j++;
	}
	r[ft_checkmany(s, c)] = 0;
	return (r);
}
