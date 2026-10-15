/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:31 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_env		t_env;
typedef struct s_command	t_command;

/* Builtins principales */
int							builtin_echo(t_command *cmd);
int							builtin_echo_bashlike(t_command *cmd);
int							builtin_cd(t_command *cmd, t_env *env);
int							builtin_pwd(void);
int							builtin_export(t_command *cmd, t_env *env);
int							builtin_unset(t_command *cmd, t_env *env);
int							builtin_env(t_env *env);
int							builtin_exit(t_command *cmd, t_env *env);

#endif