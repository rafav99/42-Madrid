/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:42:50 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/10/14 18:19:38 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstru(unsigned int n, int *count)
{
	unsigned int	rest;

	if (n > 0)
	{
		rest = n % 10 + '0';
		n = n / 10;
		ft_putstru(n, count);
		write(1, &rest, 1);
		*count = *count + 1;
	}
}

int	ft_putstr(int n, int *count)
{
	int	rest;

	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		*count = *count + 11;
		return (0);
	}
	if (n < 0)
	{
		n = n * -1;
		write(1, "-", 1);
		*count = *count + 1;
	}
	if (n > 0)
	{
		rest = n % 10 + '0';
		n = n / 10;
		ft_putstr(n, count);
		write(1, &rest, 1);
		*count = *count + 1;
	}
	return (0);
}
