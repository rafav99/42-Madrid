/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:00 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_var	*create_env_var(char *name, char *value)
{
	t_env_var	*var;

	var = (t_env_var *)ft_malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->name = ft_strdup(name);
	if (!var->name)
	{
		free(var);
		return (NULL);
	}
	if (value)
	{
		var->value = ft_strdup(value);
		if (!var->value)
		{
			free(var->name);
			free(var);
			return (NULL);
		}
	}
	else
		var->value = NULL;
	var->next = NULL;
	return (var);
}

static int	env_vars(t_env *env, t_env_var **last, char *env_str)
{
	t_env_var	*var;
	char		*equals;

	equals = ft_strchr(env_str, '=');
	if (!equals)
		return (1);
	*equals = '\0';
	var = create_env_var(env_str, equals + 1);
	*equals = '=';
	if (!var)
	{
		free_env(env);
		return (0);
	}
	if (!env->vars)
		env->vars = var;
	else
		(*last)->next = var;
	*last = var;
	return (1);
}

t_env	*init_env(char **envp)
{
	t_env		*env;
	t_env_var	*last;
	int			i;

	env = (t_env *)ft_malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->vars = NULL;
	env->last_status = 0;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		if (!env_vars(env, &last, envp[i]))
			return (NULL);
		i++;
	}
	return (env);
}

int	set_env_var(t_env *env, char *name, char *value)
{
	t_env_var	*var;
	t_env_var	*new_var;
	t_env_var	*last;

	if (!env || !name)
		return (EXIT_FAILURE);
	var = find_env_var(env, name);
	if (var)
		return (old_var(var, value));
	new_var = create_env_var(name, value);
	if (!new_var)
		return (EXIT_FAILURE);
	if (!env->vars)
		env->vars = new_var;
	else
	{
		last = env->vars;
		while (last->next)
			last = last->next;
		last->next = new_var;
	}
	return (EXIT_SUCCESS);
}

char	*safe_append(char *base, const char *to_add)
{
	char	*joined;

	if (!base || !to_add)
		return (NULL);
	joined = ft_strjoin(base, to_add);
	free(base);
	return (joined);
}
