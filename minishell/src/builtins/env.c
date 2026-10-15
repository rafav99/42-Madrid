/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:46 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_env *env)
{
	t_env_var	*var;

	if (!env)
		return (EXIT_FAILURE);
	var = env->vars;
	while (var)
	{
		write(STDOUT_FILENO, var->name, ft_strlen(var->name));
		write(STDOUT_FILENO, "=", 1);
		if (var->value)
			write(STDOUT_FILENO, var->value, ft_strlen(var->value));
		write(STDOUT_FILENO, "\n", 1);
		var = var->next;
	}
	return (EXIT_SUCCESS);
}
