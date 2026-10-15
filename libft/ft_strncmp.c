/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:47:17 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/03/11 19:26:44 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*help1;
	unsigned char	*help2;

	help1 = (unsigned char *)s1;
	help2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (help1[i] != help2[i] || help1[i] == 0 || help2[i] == 0)
			return (help1[i] - help2[i]);
		i++;
	}
	return (0);
}
