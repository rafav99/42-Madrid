/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:56 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	form_str(va_list args, char **result, char **temp)
{
	char	*arg_str;

	arg_str = va_arg(args, char *);
	if (!arg_str)
		arg_str = "(null)";
	*temp = *result;
	*result = ft_strjoin(*result, arg_str);
	free(*temp);
}

static void	form_int(va_list args, char **result, char **temp)
{
	char	*str;

	str = ft_itoa(va_arg(args, int));
	if (!str)
		return ;
	*temp = *result;
	*result = ft_strjoin(*result, str);
	free(*temp);
	free(str);
}

static void	form_char(char c, char **result, char **temp)
{
	*temp = *result;
	*result = ft_strjoin(*result, (char []){c, '\0'});
	free(*temp);
}

static void	form_type(char type, va_list args, char **result, char **temp)
{
	if (type == 's')
		form_str(args, result, temp);
	else if (type == 'd')
		form_int(args, result, temp);
	else
		form_char(type, result, temp);
}

char	*ft_vsprintf(const char *format, va_list args)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			form_type(*format, args, &result, &temp);
		}
		else
		{
			temp = result;
			result = ft_strjoin(result, (char []){*format, '\0'});
			free(temp);
		}
		format++;
	}
	return (result);
}
