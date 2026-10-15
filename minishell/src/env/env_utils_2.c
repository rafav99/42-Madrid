/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:02 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_env_var(t_env *env, char *name)
{
	t_env_var	*var;
	t_env_var	*prev;

	if (!env || !name)
		return (EXIT_FAILURE);
	prev = NULL;
	var = env->vars;
	while (var)
	{
		if (ft_strcmp(var->name, name) == 0)
		{
			if (prev)
				prev->next = var->next;
			else
				env->vars = var->next;
			free(var->name);
			if (var->value)
				free(var->value);
			free(var);
			return (EXIT_SUCCESS);
		}
		prev = var;
		var = var->next;
	}
	return (EXIT_SUCCESS);
}

static int	count_env_vars(t_env *env)
{
	t_env_var	*var;
	int			count;

	count = 0;
	var = env->vars;
	while (var)
	{
		count++;
		var = var->next;
	}
	return (count);
}

static int	fill_env_array(char **array, t_env_var *var)
{
	char	*tmp;
	int		i;

	i = 0;
	while (var)
	{
		if (var->value)
		{
			tmp = ft_strjoin(var->name, "=");
			array[i] = ft_strjoin(tmp, var->value);
			free(tmp);
		}
		else
			array[i] = ft_strdup(var->name);
		if (!array[i])
		{
			free_env_array(array);
			return (-1);
		}
		var = var->next;
		i++;
	}
	array[i] = NULL;
	return (0);
}

char	**env_to_array(t_env *env)
{
	char		**array;
	int			count;

	if (!env)
		return (NULL);
	count = count_env_vars(env);
	array = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	if (fill_env_array(array, env->vars) == -1)
		return (NULL);
	return (array);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
