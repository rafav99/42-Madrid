/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:03:28 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/10/14 18:20:58 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

void	ft_putstrhex1(unsigned long long n, int *count);
void	ft_putstrhex(unsigned int n, int *count);
void	ft_putstrhexmay(unsigned int n, int *count);
int		ft_printf(const char *str, ...);
size_t	ft_strlen(const char *str);
void	ft_putstru(unsigned int n, int *count);
int		ft_putstr(int n, int *count);
void	ft_writep(va_list mylist, char choice, int *count);
void	ft_writehex(va_list mylist, char choice, int *count);
void	ft_writedec(va_list mylist, char choice, int *count);
void	ft_writelet(va_list mylist, char choice, int *count);

char *ft_vsprintf(const char *format, va_list args);
int ft_dprintf(int fd, const char *format, ...);
#endif