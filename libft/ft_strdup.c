/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:25:34 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/10 14:25:37 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		i;
	int		l;

	l = ft_strlen(s);
	p = malloc(l + 1);
	i = 0;
	if (p == 0)
		return (NULL);
	while (i <= (int)l)
	{
		p[i] = s[i];
		i++;
	}
	return (p);
}
