/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:43 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	write_args(t_command *cmd, int *i)
{
	int		n_flag;
	ssize_t	w_res;

	n_flag = 0;
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
		n_flag = 1;
	*i = 1 + n_flag;
	while (cmd->args[*i])
	{
		w_res = write(STDOUT_FILENO, cmd->args[*i], ft_strlen(cmd->args[*i]));
		if (w_res == -1)
			return (EXIT_FAILURE);
		if (cmd->args[*i + 1])
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (EXIT_FAILURE);
		}
		*i = *i + 1;
	}
	if (!n_flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	builtin_echo(t_command *cmd)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->args[0])
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!cmd->args[1])
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (write_args(cmd, &i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	write_bashlike(t_command *cmd)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	if (cmd->args[1] && ft_strcmp(cmd->args[1], "-n") == 0)
		n_flag = 1;
	i = 1 + n_flag;
	while (cmd->args[i])
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!n_flag)
		write(STDOUT_FILENO, "\n", 1);
}

int	builtin_echo_bashlike(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (!cmd->args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
