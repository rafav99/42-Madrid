/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:04 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_env *env)
{
	t_env_var	*var;
	t_env_var	*next;

	if (!env)
		return ;
	var = env->vars;
	while (var)
	{
		next = var->next;
		if (var->name)
			free(var->name);
		if (var->value)
			free(var->value);
		free(var);
		var = next;
	}
	free(env);
}

t_env_var	*find_env_var(t_env *env, char *name)
{
	t_env_var	*var;

	if (!env || !name)
		return (NULL);
	var = env->vars;
	while (var)
	{
		if (ft_strcmp(var->name, name) == 0)
			return (var);
		var = var->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *env, char *name)
{
	t_env_var	*var;

	if (!env || !name)
		return (NULL);
	var = find_env_var(env, name);
	if (var && var->value)
		return (var->value);
	return (NULL);
}

int	old_var(t_env_var *var, char *value)
{
	if (var->value)
		free(var->value);
	if (value)
		var->value = ft_strdup(value);
	else
		var->value = NULL;
	return (EXIT_SUCCESS);
}
