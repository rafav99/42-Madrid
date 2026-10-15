/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:10:35 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/04/16 16:10:38 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_numbwrite(int n, int fd)
{
	int	resto;

	if (n != 0)
	{
		resto = '0' + n % 10;
		n = n / 10;
		ft_numbwrite(n, fd);
		write(fd, &resto, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		write(fd, &"0", 1);
	}
	else if (n == -2147483648)
	{
		write(fd, &"-", 1);
		write(fd, &"2", 1);
		ft_numbwrite(147483648, fd);
	}
	else if (n < 0)
	{
		n = -n;
		write(fd, &"-", 1);
	}
	if (n != 0 && n != -2147483648)
		ft_numbwrite(n, fd);
}
