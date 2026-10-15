/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 18:03:28 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/03/06 19:24:09 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>

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
char	*get_next_line(int fd);
void	ft_loop(char const *s, unsigned int start, size_t len, char *p);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		check_buff(char *buffer);
void	join_aux(char *s1, char const *s2, char *p);
char	*ft_strjoin(char *s1, char const *s2);
void	before(char *str, char **alline, char **save);
char	*read_line(char *alline, char **save, int fd);
void	savelong(char **save);

#endif