/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:36 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	oldpwd_err(char *path, t_env *env, char *old_pwd)
{
	if (!old_pwd)
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		free(old_pwd);
		print_exec_error("cd", errno);
		return (EXIT_FAILURE);
	}
	set_env_var(env, "OLDPWD", old_pwd);
	free(old_pwd);
	return (EXIT_SUCCESS);
}

int	manage_cwd(char *path, t_env *env)
{
	char	cwd[1024];
	char	*old_pwd;
	char	*new_pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		print_exec_error("cd", errno);
		return (EXIT_FAILURE);
	}
	old_pwd = ft_strdup(cwd);
	if (oldpwd_err(path, env, old_pwd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		new_pwd = ft_strdup(cwd);
		if (new_pwd)
		{
			set_env_var(env, "PWD", new_pwd);
			free(new_pwd);
		}
	}
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_command *cmd, t_env *env)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			print_shell_error("cd", "HOME not set");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if (cmd->args[2])
		{
			print_shell_error("cd", "too many arguments");
			return (EXIT_FAILURE);
		}
		path = cmd->args[1];
	}
	if (manage_cwd(path, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
