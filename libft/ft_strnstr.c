/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:25:16 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/10 14:25:18 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*str, const char *to_find, size_t len)
{
	size_t	iter;
	size_t	c;

	iter = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[iter] != '\0' && iter < len)
	{
		if (str[iter] == to_find[0])
		{
			c = 0;
			while (to_find[c] != '\0' && iter + c < len)
			{
				if (str[iter + c] == to_find[c] && to_find[c + 1] == '\0')
					return ((char *)&str[iter]);
				else if (str[iter + c] != to_find[c])
					break ;
				c++;
			}
		}
		iter++;
	}
	return (NULL);
}
