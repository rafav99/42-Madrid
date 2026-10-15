/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:58:00 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/10/14 18:40:44 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_writep(va_list mylist, char choice, int *count)
{
	unsigned long long	arg;

	if (choice == 'p')
	{
		arg = va_arg(mylist, unsigned long long);
		write(1, "0x", 2);
		*count = *count + 2;
		ft_putstrhex1(arg, count);
		if (arg == 0)
		{
			write(1, "0", 1);
			*count = *count + 1;
		}
	}
	if (choice == '%')
	{
		write(1, "%", 1);
		*count = *count + 1;
	}
}

void	ft_writehex(va_list mylist, char choice, int *count)
{
	unsigned int	argument;

	if (choice == 'x')
	{
		argument = (unsigned int)va_arg(mylist, int);
		if (argument == 0)
		{
			write(1, "0", 1);
			*count = *count + 1;
		}
		ft_putstrhex(argument, count);
	}
	if (choice == 'X')
	{
		argument = va_arg(mylist, unsigned int);
		if (argument == 0)
		{
			write(1, "0", 1);
			*count = *count + 1;
		}
		ft_putstrhexmay(argument, count);
	}
}

void	ft_writedec(va_list mylist, char choice, int *count)
{
	int	argument;

	if (choice == 'i' || choice == 'd')
	{
		argument = va_arg(mylist, int);
		if (argument == 0)
		{
			write(1, "0", 1);
			*count = *count + 1;
		}
		ft_putstr(argument, count);
	}
	if (choice == 'u')
	{
		argument = va_arg(mylist, int);
		if (argument == 0)
		{
			write(1, "0", 1);
			*count = *count + 1;
		}
		ft_putstru(argument, count);
	}
}

void	ft_writelet(va_list mylist, char choice, int *count)
{
	int		argument;
	char	*arg_str;

	if (choice == 'c')
	{
		argument = va_arg(mylist, int);
		write(1, &argument, 1);
		if (choice != 0)
			*count = *count + 1;
	}
	if (choice == 's')
	{
		arg_str = va_arg(mylist, char *);
		if (arg_str != NULL)
		{
			write(1, arg_str, ft_strlen(arg_str));
			*count = *count + ft_strlen(arg_str);
		}
		else
		{
			write(1, "(null)", 6);
			*count = *count + 6;
		}
	}
}
