/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:19 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_commands(t_command *cmd_list)
{
	int	count;

	count = 0;
	while (cmd_list)
	{
		count++;
		cmd_list = cmd_list->next;
	}
	return (count);
}

int	check_brk_pipe(t_command *cmd_list)
{
	t_redir		*redir;
	t_command	*second;

	if (cmd_list && cmd_list->next && !cmd_list->next->next)
	{
		second = cmd_list->next;
		if (second->redirects)
		{
			redir = second->redirects;
			while (redir)
			{
				if (redir->type == TOKEN_REDIR_IN)
					return (1);
				redir = redir->next;
			}
		}
	}
	return (0);
}

static int	check_status(int i, int num_cmds, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (i == num_cmds - 1)
			return (128 + sig);
	}
	else if (WIFEXITED(status))
	{
		if (i == num_cmds - 1)
			return (WEXITSTATUS(status));
	}
	else if (i == num_cmds - 1)
		return (EXIT_FAILURE);
	return (-1);
}

int	wait_child(pid_t *pids, int num_cmds, t_command *cmd_list)
{
	int	status;
	int	i;
	int	last_status;
	int	new_status;

	(void)cmd_list;
	i = 0;
	last_status = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) != -1)
		{
			new_status = check_status(i, num_cmds, status);
			if (new_status != -1)
				last_status = new_status;
		}
		i++;
	}
	return (last_status);
}
