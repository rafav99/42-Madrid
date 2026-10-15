/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 11:21:19 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/03/12 11:50:11 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, unsigned int size)
{
	char			*ptr;
	unsigned int	tik;

	ptr = dest + ft_strlen(dest);
	tik = ft_strlen(dest);
	if (size < ft_strlen(dest))
		return (ft_strlen(src) + size);
	while (tik < size - 1 && *src != '\0' && size >= 2)
	{
		*ptr = *src;
		ptr++;
		src++;
		tik++;
	}
	if (size != 0)
		*ptr = '\0';
	return (ft_strlen(dest) + ft_strlen(src));
}
