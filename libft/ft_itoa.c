/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:09:52 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 13:09:55 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_count(int n)
{
	int		count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	if (n == 0)
		count++;
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_putstr(char *p, int n, int negative)
{
	int	i;
	int	rest;

	if (n == 0)
		p[0] = '0';
	i = ft_count(n) - 1;
	if (negative == 1)
		i++;
	p[i + 1] = '\0';
	while (n > 0)
	{
		rest = n % 10 + '0';
		n = n / 10;
		p[i] = rest;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*p;
	int		negative;

	if (n == -2147483648)
	{
		p = malloc(12);
		if (p == NULL)
			return (NULL);
		ft_strlcpy(p, "-2147483648", 12);
		return (p);
	}
	negative = 0;
	p = malloc(ft_count(n) + 1);
	if (p == NULL)
		return (NULL);
	if (n < 0)
	{	
		n = n * -1;
		p[0] = '-';
		negative = 1;
	}
	ft_putstr(p, n, negative);
	return (p);
}
