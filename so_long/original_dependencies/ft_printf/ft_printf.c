/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:42:44 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/10/14 18:37:16 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printall(va_list mylist, int *count, const char *str)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (str[i] == '%')
		{
			i++;
			ft_writep(mylist, str[i], count);
			ft_writelet(mylist, str[i], count);
			ft_writedec(mylist, str[i], count);
			ft_writehex(mylist, str[i], count);
			i++;
		}
		if (str[i] != 0 && str[i] != '%')
		{
			write(1, &str[i], 1);
			*count = *count + 1;
			i++;
		}
	}
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	mylist;

	count = 0;
	va_start(mylist, str);
	ft_printall(mylist, &count, str);
	va_end(mylist);
	return (count);
}
