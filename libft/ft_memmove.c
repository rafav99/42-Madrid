/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 10:39:04 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/08 10:39:07 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int				i;
	unsigned char	*p;
	unsigned char	*r;

	p = (unsigned char *)dest;
	r = (unsigned char *)src;
	i = 0;
	if (dest == 0 && src == 0)
		return (NULL);
	if (dest < src)
	{
		while (i < (int)n)
		{
			p[i] = r[i];
			i++;
		}
	}
	else
		while (n--)
			p[n] = r[n];
	return (dest);
}
