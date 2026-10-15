/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:43 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:55:10 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include <stdarg.h>
# include <stddef.h>

/* Utilidades de memoria */
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	free_array(char **array);

/* Utilidades de error */
void	print_error(char *cmd, char *msg);
void	print_error_exit(char *cmd, char *msg, int exit_code);

/* Shared functions are declared in libft.h and ft_printf.h. */
/* String utilities */
int		count_words(char const *s, char c);
char **ft_split_cmd(char const *s, char c);
#endif