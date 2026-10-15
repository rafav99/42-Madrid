/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:44:16 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/09 10:44:18 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (p[i] == (unsigned char)c)
			return (&p[i]);
		i--;
	}
	return (0);
}
