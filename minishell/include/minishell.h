/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:37 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/21 05:30:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/* Incluir primero utils.h ya que muchos otros módulos dependerán de él */
# include "builtins.h"
# include "env.h"
# include "executor.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"
# include "libft.h"
# include "ft_printf.h"

# define SUCCESS 0
# define ERROR 1
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_COMMAND_NOT_FOUND 127

# define PROMPT "minishell$ "

/* Variables globales */
extern int			g_signal;

/* Funciones principales */
void				init_shell(char **envp, t_env **g_env);
void				run_shell(t_env **g_env);
void				cleanup_shell(t_env **g_env);

/* Utils */

/* Error handling functions */
void				print_exec_error(const char *cmd, int err);
void				print_cmd_not_found(const char *cmd);
void				print_shell_error(const char *context, const char *message);
void				print_syntax_error(const char *message);

// Funciones de utilidad para el entorno
char				*get_env_value(t_env *env, char *name);
int					set_env_var(t_env *env, char *name, char *value);
int					unset_env_var(t_env *env, char *name);
char				**env_to_array(t_env *env);
void				free_env_array(char **env_array);
char				*safe_append(char *base, const char *to_add);

#endif