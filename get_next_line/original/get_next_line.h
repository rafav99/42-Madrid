/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:24 by rvaldes-          #+#    #+#             */
/*   Updated: 2021/11/22 13:12:43 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
void	ft_loop(char const *s, unsigned int start, size_t len, char *p);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		check_buff(char *buffer);
void	join_aux(char *s1, char const *s2, char *p);
char	*ft_strjoin(char *s1, char const *s2);
void	before(char *str, char **alline, char **save);
char	*read_line(char *alline, char **save, int fd);
void	savelong(char **save);

#endif