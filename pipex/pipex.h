/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaldes- <rvaldes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:56:18 by rvaldes-          #+#    #+#             */
/*   Updated: 2023/08/21 18:01:03 by rvaldes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define READ_END 0
# define WRITE_END 1

typedef struct t_commands
{
	char	*path_line;
	char	**paths;
	char	**envp;
	char	**cmd;
	int		argnum;

}t_commands;

typedef struct t_files
{
	int	infile;
	int	outfile;
}t_files;

void	get_cmd(t_commands *my_comm, int *activate, int i);
void	execute(t_commands *my_comm);
void	firstprocess(t_commands *my_comm, int list[1][2], int infile);
void	lastprocess(t_commands *my_comm, int i, int list[1][2], int outfile);
void	midprocess(t_commands *my_comm, int i, int list[1][2]);
void	pstart(char *argv[], t_commands *my_comm, int infile, int outfile);
void	check_files(int argc, char *argv[], int *infile, int *outfile);
void	get_path(t_commands *my_comm, int argc, char *envp[]);

#endif