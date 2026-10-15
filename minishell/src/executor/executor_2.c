/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:10 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (EXIT_FAILURE);
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (builtin_echo(cmd));
	else if (!ft_strcmp(cmd->args[0], "cd"))
		return (builtin_cd(cmd, env));
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return (builtin_pwd());
	else if (!ft_strcmp(cmd->args[0], "export"))
		return (builtin_export(cmd, env));
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return (builtin_unset(cmd, env));
	else if (!ft_strcmp(cmd->args[0], "env"))
		return (builtin_env(env));
	else if (!ft_strcmp(cmd->args[0], "exit"))
		return (builtin_exit(cmd, env));
	return (EXIT_FAILURE);
}

static void	handle_invalid_cmd(t_command *cmd, char *cmd_path)
{
	if (ft_strchr(cmd->args[0], '/') && errno == ENOENT)
	{
		print_error(cmd->args[0], "No such file or directory");
		free(cmd_path);
		exit(127);
	}
}

static void	check_cmd_file_stat(t_command *cmd, char *cmd_path)
{
	struct stat	file_stat;

	if (stat(cmd_path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", cmd->args[0]);
			free(cmd_path);
			exit(126);
		}
		if (file_stat.st_size == 0)
		{
			free(cmd_path);
			exit(0);
		}
		if (access(cmd_path, X_OK) != 0)
		{
			print_error(cmd->args[0], "permission denied");
			free(cmd_path);
			exit(126);
		}
	}
}

int	execute_external_child(t_command *cmd, t_env *env)
{
	char		*cmd_path;
	char		**env_array;

	if (!cmd->args || !cmd->args[0] || !*cmd->args[0])
		exit(0);
	cmd_path = find_command_path(cmd->args[0], env);
	if (!cmd_path)
	{
		print_error(cmd->args[0], "command not found");
		exit(127);
	}
	handle_invalid_cmd(cmd, cmd_path);
	check_cmd_file_stat(cmd, cmd_path);
	env_array = env_to_array(env);
	if (!env_array)
	{
		free(cmd_path);
		exit(1);
	}
	execve(cmd_path, cmd->args, env_array);
	print_error(cmd->args[0], strerror(errno));
	free_array(env_array);
	free(cmd_path);
	exit(126);
}
