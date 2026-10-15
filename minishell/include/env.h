/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:53:35 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:53:36 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_env_var
{
	char				*name;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_env
{
	t_env_var			*vars;
	int					last_status;
}						t_env;

/* Funciones de inicialización y limpieza */
t_env					*init_env(char **envp);
void					free_env(t_env *env);

/* Funciones de manejo de variables */
t_env_var				*find_env_var(t_env *env, char *name);
char					*get_env_value(t_env *env, char *name);
int						set_env_var(t_env *env, char *name, char *value);
int						unset_env_var(t_env *env, char *name);

/* Funciones de conversión */
char					**env_to_array(t_env *env);
void					free_env_array(char **env_array);

/* Funciones de expansión de variables */
char					*expand_env_variables(char *str, t_env *env);
char					*safe_append(char *base, const char *to_add);
t_env_var				*create_env_var(char *name, char *value);
int						old_var(t_env_var *var, char *value);
int						append_var_sign(char **res, int *i);
int						append_value(char **res, char *val);
int						status_var_sign(char *str, t_env *env, char **res,
							int *i);

#endif