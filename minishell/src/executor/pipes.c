/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:21 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	create_pipes(int pipes[2][2], int cmd_count)
{
	int	i;

	if (cmd_count <= 1)
		return (0);
	i = 0;
	while (i < cmd_count - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			print_error("pipe", strerror(errno));
			return (-1);
		}
		i++;
	}
	return (0);
}

void	close_pipes(int pipes[2][2], int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	setup_pipe_fds(int pipes[2][2], int i, int cmd_count)
{
	if (i == 0)
	{
		if (cmd_count > 1)
		{
			close(pipes[i][0]);
			dup2(pipes[i][1], STDOUT_FILENO);
			close(pipes[i][1]);
		}
	}
	else if (i == cmd_count - 1)
	{
		close(pipes[i - 1][1]);
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
	else
	{
		close(pipes[i - 1][1]);
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
		close(pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
}
