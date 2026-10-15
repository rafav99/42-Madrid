/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:38:11 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/08 10:38:13 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*p;
	unsigned char	*l;

	p = (unsigned char *)s1;
	l = (unsigned char *)s2;
	i = 0;
	while (i < (int)n)
	{
		if (p[i] != l[i])
			return (p[i] - l[i]);
		i++;
	}
	return (0);
}
