/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:13 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	execute_external_command(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		execute_external_child(cmd, env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = EXIT_FAILURE;
	}
	else
	{
		print_error("fork", strerror(errno));
		status = EXIT_FAILURE;
	}
	return (status);
}

int	execute_options(t_command *cmd, t_env *env)
{
	int	status;

	status = 0;
	if (is_builtin(cmd->args[0]))
		status = execute_builtin(cmd, env);
	else
		status = execute_external_command(cmd, env);
	return (status);
}

static void	restore_std(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

int	execute_simple_command(t_command *cmd, t_env *env)
{
	int	stdin_backup;
	int	stdout_backup;
	int	status;

	stdin_backup = -1;
	stdout_backup = -1;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_SUCCESS);
	if (cmd->redirects)
	{
		if (h_redirections(cmd, &stdin_backup, &stdout_backup) == -1)
			return (EXIT_FAILURE);
	}
	status = execute_options(cmd, env);
	restore_std(stdin_backup, stdout_backup);
	return (status);
}
