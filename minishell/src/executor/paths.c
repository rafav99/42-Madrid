/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:17 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
		return (S_ISDIR(path_stat.st_mode));
	return (0);
}

static char	*direct_path(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		errno = ENOENT;
		return (ft_strdup(cmd));
	}
	if (is_directory(cmd))
	{
		errno = EISDIR;
		return (ft_strdup(cmd));
	}
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	errno = EACCES;
	return (ft_strdup(cmd));
}

static char	*create_path(char **paths, char *cmd, int i)
{
	char	*cmd_path;
	char	*temp;

	temp = ft_strjoin(paths[i], "/");
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	if (cmd_path && is_directory(cmd_path))
	{
		errno = EISDIR;
		free_array(paths);
		return (cmd_path);
	}
	if (access(cmd_path, X_OK) == 0)
	{
		free_array(paths);
		return (cmd_path);
	}
	free(cmd_path);
	return (NULL);
}

static char	*search_in_path(char **paths, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = create_path(paths, cmd, i);
		if (cmd_path)
			return (cmd_path);
		i++;
	}
	free_array(paths);
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (direct_path(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split_cmd(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path(paths, cmd));
}
