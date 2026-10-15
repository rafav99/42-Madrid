/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:43:00 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/10/14 18:19:30 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstrhex(unsigned int n, int *count)
{
	unsigned int	rest;

	if (n > 0)
	{
		if (n % 16 < 10)
			rest = n % 16 + '0';
		if (n % 16 >= 10)
			rest = n % 16 - 10 + 'a';
		n = n / 16;
		ft_putstrhex(n, count);
		write(1, &rest, 1);
		*count = *count + 1;
	}
}

void	ft_putstrhex1(unsigned long long n, int *count)
{
	unsigned long long	rest;

	if (n > 0)
	{
		if (n % 16 < 10)
			rest = n % 16 + '0';
		if (n % 16 >= 10)
			rest = n % 16 - 10 + 'a';
		n = n / 16;
		ft_putstrhex1(n, count);
		write(1, &rest, 1);
		*count = *count + 1;
	}
}

void	ft_putstrhexmay(unsigned int n, int *count)
{
	unsigned int	rest;

	if (n > 0)
	{
		if (n % 16 < 10)
			rest = n % 16 + '0';
		if (n % 16 >= 10)
			rest = n % 16 - 10 + 'A';
		n = n / 16;
		ft_putstrhexmay(n, count);
		write(1, &rest, 1);
		*count = *count + 1;
	}
}
