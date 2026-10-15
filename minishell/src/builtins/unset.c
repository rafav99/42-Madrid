/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:55 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	builtin_unset(t_command *cmd, t_env *env)
{
	int	i;
	int	result;
	int	final_result;

	if (!cmd->args[1])
		return (EXIT_SUCCESS);
	i = 1;
	final_result = EXIT_SUCCESS;
	while (cmd->args[i])
	{
		if (!is_valid_var_name(cmd->args[i]))
		{
			print_error("unset", "not a valid identifier");
			final_result = EXIT_FAILURE;
		}
		else
		{
			result = unset_env_var(env, cmd->args[i]);
			if (result != EXIT_SUCCESS)
				final_result = result;
		}
		i++;
	}
	return (final_result);
}
