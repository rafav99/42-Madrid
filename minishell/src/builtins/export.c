/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:50 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/21 06:24:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_exported_vars(t_env *env)
{
	t_env_var	*var;

	var = env->vars;
	while (var)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, var->name, ft_strlen(var->name));
		if (var->value)
		{
			write(STDOUT_FILENO, "=\"", 2);
			write(STDOUT_FILENO, var->value, ft_strlen(var->value));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}
}

static int	is_valid_var_name(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!((*name >= 'a' && *name <= 'z') || (*name >= 'A' && *name <= 'Z')
			|| *name == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A'
					&& name[i] <= 'Z') || (name[i] >= '0' && name[i] <= '9')
				|| name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	validate_and_set_var(char *name, char *value, t_env *env)
{
	if (!is_valid_var_name(name))
	{
		print_error("export", "not a valid identifier");
		return (EXIT_FAILURE);
	}
	return (set_env_var(env, name, value));
}

static int	process_export_arg(char *arg, t_env *env)
{
	char	*equals;
	char	*name;
	char	*value;
	char	*arg_copy;

	arg_copy = ft_strdup(arg);
	if (!arg_copy)
		return (EXIT_FAILURE);
	equals = ft_strchr(arg_copy, '=');
	if (!equals)
	{
		if (!is_valid_var_name(arg_copy))
		{
			free(arg_copy);
			print_error("export", "not a valid identifier");
			return (EXIT_FAILURE);
		}
		free(arg_copy);
		return (EXIT_SUCCESS);
	}
	*equals = '\0';
	name = arg_copy;
	value = equals + 1;
	return (validate_and_set_var(name, value, env));
}

int	builtin_export(t_command *cmd, t_env *env)
{
	int	i;
	int	result;
	int	final_result;

	if (!cmd->args[1])
	{
		print_exported_vars(env);
		return (EXIT_SUCCESS);
	}
	i = 1;
	final_result = EXIT_SUCCESS;
	while (cmd->args[i])
	{
		result = process_export_arg(cmd->args[i], env);
		if (result != EXIT_SUCCESS)
			final_result = result;
		i++;
	}
	return (final_result);
}
