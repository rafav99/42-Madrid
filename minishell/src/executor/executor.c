/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:15 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	close_fds(int fd_in, int fd_out[2], t_command *cmd)
{
	if (fd_in != -1)
		close(fd_in);
	if (fd_out)
	{
		if (fd_out[0] != -1)
			close(fd_out[0]);
		if (fd_out[1] != -1)
			close(fd_out[1]);
	}
	if (cmd->redirects && setup_redirections(cmd->redirects) == -1)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static void	redirect_input(int fd_in, int fd_out[2])
{
	if (fd_in != -1)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			print_error("dup2", "Failed to redirect stdin for pipe");
			close(fd_in);
			if (fd_out)
			{
				close(fd_out[0]);
				close(fd_out[1]);
			}
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
}

static void	pipe_fds(int fd_in, int fd_out[2])
{
	redirect_input(fd_in, fd_out);
	if (fd_out)
	{
		if (fd_out[1] != -1)
		{
			if (dup2(fd_out[1], STDOUT_FILENO) == -1)
			{
				print_error("dup2", "Failed to redirect stdout for pipe");
				close(fd_out[1]);
				close(fd_out[0]);
				exit(EXIT_FAILURE);
			}
			close(fd_out[1]);
		}
		close(fd_out[0]);
	}
}

void	ex_pl_command(t_command *cmd, t_env *env, int fd_in, int fd_out[2])
{
	setup_child_signals();
	if (!cmd->args || !cmd->args[0] || !*cmd->args[0])
		close_fds(fd_in, fd_out, cmd);
	pipe_fds(fd_in, fd_out);
	if (cmd->redirects && setup_redirections(cmd->redirects) == -1)
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, env));
	else
		execute_external_child(cmd, env);
}

int	execute_commands(t_command *cmd, t_env *env)
{
	int	exit_status;

	if (!cmd)
		return (EXIT_SUCCESS);
	if (!cmd->next)
		exit_status = execute_simple_command(cmd, env);
	else
		exit_status = execute_pipeline(cmd, env);
	env->last_status = exit_status;
	return (exit_status);
}
