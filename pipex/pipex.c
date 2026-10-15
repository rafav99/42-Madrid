/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:42:24 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/08/23 19:01:51 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pstart(char *argv[], t_commands *my_comm, int infile, int outfile)
{
	int	i;
	int	(*list)[2];
	int	status;

	i = 2;
	list = (int (*)[2])malloc((my_comm->argnum - 3) * sizeof(int [2]));
	while (i < my_comm->argnum - 1)
	{
		my_comm->cmd = ft_split(argv[i], ' ');
		if (i == 2)
			firstprocess(my_comm, list, infile);
		else if (i == my_comm->argnum - 2)
			lastprocess(my_comm, i, list, outfile);
		else
			midprocess(my_comm, i, list);
		i++;
	}
	i = 2;
	while (i < my_comm->argnum - 1)
	{
		wait(&status);
		i++;
	}
	free(list);
}

void	check_files(int argc, char *argv[], int *infile, int *outfile)
{
	if (argc < 5)
		exit(1);
	*outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT , 0666);
	if (!(access(argv[1], F_OK) == 0))
	{
		ft_printf("pipex: %s: no such file or directory \n", argv[1]);
		*infile = -1;
	}
	else if (!(access(argv[1], R_OK) == 0))
	{
		ft_printf("pipex: permission denied: %s\n", argv[1]);
		*infile = -1;
	}
	else
		*infile = open(argv[1], O_RDONLY);
	if (!(access(argv[argc - 1], W_OK) == 0))
		ft_printf("pipex: permission denied: %s\n", argv[argc - 1]);
}

void	get_path(t_commands *my_comm, int argc, char *envp[])
{
	int		i;
	char	*path_line;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path_line = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	my_comm->argnum = argc;
	my_comm->paths = ft_split(path_line, ':');
	i = 0;
	while (my_comm->paths && my_comm->paths[i] != NULL)
	{
		my_comm->paths[i] = ft_strjoin(my_comm->paths[i], "/");
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int			outfile;
	int			infile;
	t_commands	my_comm;

	my_comm.envp = envp;
	check_files(argc, argv, &infile, &outfile);
	get_path(&my_comm, argc, envp);
	pstart(argv, &my_comm, infile, outfile);
	return (0);
}
