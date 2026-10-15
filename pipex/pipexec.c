/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:42:30 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/08/21 18:01:50 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd(t_commands *my_comm, int *activate, int i)
{
	char	*fcmd;
	char	*notfound;

	if (ft_strnstr(my_comm->cmd[0], "../", 3) == NULL
		&& ft_strnstr(my_comm->cmd[0], "./", 2) == NULL
		&& ft_strnstr(my_comm->cmd[0], "/", 1) == NULL)
		fcmd = ft_strjoin(my_comm->paths[i], my_comm->cmd[0]);
	else
	{
		fcmd = ft_strjoin("", my_comm->cmd[0]);
		if (!(access(fcmd, F_OK) == 0))
		{	
			notfound = ft_strjoin("pipex: no such file or directory: ", fcmd);
			ft_putendl_fd(notfound, 2);
			exit(1);
		}
	}
	if (access(fcmd, F_OK) == 0)
	{
		*activate = 1;
		execve(fcmd, my_comm->cmd, my_comm->envp);
	}
	free(fcmd);
}

void	execute(t_commands *my_comm)
{
	int		i;
	int		activate;
	char	*notfound;

	i = 0;
	activate = 0;
	while (my_comm->paths[i] != NULL)
	{
		get_cmd(my_comm, &activate, i);
		i++;
	}
	if (activate == 0)
	{
		notfound = ft_strjoin("pipex: command not found: ", my_comm->cmd[0]);
		ft_putendl_fd(notfound, 2);
		exit(1);
	}
}

void	firstprocess(t_commands *my_comm, int list[1][2], int infile)
{
	int	pid;

	pipe(list[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2(infile, STDIN_FILENO);
		close(list[0][READ_END]);
		dup2(list[0][WRITE_END], STDOUT_FILENO);
		close(list[0][WRITE_END]);
		if (infile == -1)
			exit(2);
		execute(my_comm);
	}
}

void	lastprocess(t_commands *my_comm, int i, int list[1][2], int outfile)
{	
	int	pid;

	close(list[i - 3][WRITE_END]);
	if (i > 3)
		close(list[i - 4][READ_END]);
	pid = fork();
	if (pid == 0)
	{
		dup2(list[i - 3][READ_END], STDIN_FILENO);
		close(list[i - 3][0]);
		dup2(outfile, STDOUT_FILENO);
		execute(my_comm);
	}
	close(list[i - 3][READ_END]);
}

void	midprocess(t_commands *my_comm, int i, int list[1][2])
{
	int	pid;

	close(list[i - 3][WRITE_END]);
	pipe(list[i - 2]);
	pid = fork();
	if (pid == 0)
	{
		close(list[i - 2][READ_END]);
		dup2(list[i - 3][READ_END], STDIN_FILENO);
		close(list[i - 3][READ_END]);
		dup2(list[i - 2][WRITE_END], STDOUT_FILENO);
		close(list[i - 2][WRITE_END]);
		execute(my_comm);
	}
}
