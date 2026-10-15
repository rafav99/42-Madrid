/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:08 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 18:30:10 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static pid_t	*init_pipeline(t_command *cmd_list, t_pipeline *pl)
{
	pid_t	*pids;

	pl->cmd_index = 0;
	pl->last_status = 0;
	pl->fd_in = -1;
	check_brk_pipe(cmd_list);
	pids = ft_malloc(sizeof(pid_t) * count_commands(cmd_list));
	return (pids);
}

static int	h_error(int *fd, t_pipeline *pl, pid_t *pids, int is_p_err)
{
	if (is_p_err)
		print_error("pipe", strerror(errno));
	else
		print_error("fork", strerror(errno));
	if (!pl->is_last)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (pl->fd_in != -1)
		close(pl->fd_in);
	free(pids);
	return (EXIT_FAILURE);
}

static void	parent_process(t_pipeline *pl, int *fd, pid_t *pids, pid_t pid)
{
	pids[pl->cmd_index++] = pid;
	if (!pl->is_last)
		close(fd[1]);
	if (pl->fd_in != -1)
		close(pl->fd_in);
	pl->fd_in = -1;
	if (!pl->is_last)
		pl->fd_in = fd[0];
}

static int	ex_pl_aux(t_command *cmd, t_env *env, t_pipes *pipes, int *fd)
{
	pid_t	pid;

	pipes->pl.is_last = (cmd->next == NULL);
	if (!pipes->pl.is_last)
	{
		if (pipe(fd) == -1)
			return (h_error(fd, &pipes->pl, pipes->pids, 1));
	}
	pid = fork();
	if (pid == -1)
		return (h_error(fd, &pipes->pl, pipes->pids, 0));
	if (pid == 0)
	{
		free(pipes->pids);
		if (pipes->pl.is_last)
			ex_pl_command(cmd, env, pipes->pl.fd_in, NULL);
		else
			ex_pl_command(cmd, env, pipes->pl.fd_in, fd);
	}
	parent_process(&pipes->pl, fd, pipes->pids, pid);
	return (0);
}

int	execute_pipeline(t_command *cmd_list, t_env *env)
{
	int			fd[2];
	t_command	*current_cmd;
	t_pipes		pipes;

	pipes.pids = init_pipeline(cmd_list, &pipes.pl);
	if (!pipes.pids)
		return (EXIT_FAILURE);
	current_cmd = cmd_list;
	while (current_cmd)
	{
		if (ex_pl_aux(current_cmd, env, &pipes, fd) != 0)
			return (EXIT_FAILURE);
		current_cmd = current_cmd->next;
	}
	pipes.pl.last_status = wait_child(pipes.pids, count_commands(cmd_list),
			cmd_list);
	free(pipes.pids);
	return (pipes.pl.last_status);
}
