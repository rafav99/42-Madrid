/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:38:49 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:11:44 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*r;

	p = (unsigned char *)dest;
	r = (unsigned char *)src;
	i = 0;
	while (i < n && r[i] != (unsigned char)c)
	{
		*p = r[i];
		i++;
		p++;
	}
	if (r[i] == (unsigned char)c && i < n)
	{
		*p = r[i];
		return (p + 1);
	}
	else
		return (0);
}
