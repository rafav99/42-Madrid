/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:25 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_input(char *file)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error(file, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		print_error("dup2", strerror(errno));
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect_output(char *file, int append)
{
	int	fd;
	int	flags;

	if (!file)
		return (-1);
	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		print_error(file, strerror(errno));
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		print_error("dup2", strerror(errno));
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_heredoc(char *delimiter)
{
	int	fd[2];

	(void)delimiter;
	if (pipe(fd) == -1)
	{
		print_error("pipe", strerror(errno));
		return (-1);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		print_error("dup2", strerror(errno));
		close(fd[0]);
		return (-1);
	}
	close(fd[0]);
	return (0);
}

int	setup_redirections(t_redir *redirects)
{
	t_redir	*current;
	int		result;

	current = redirects;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN)
			result = redirect_input(current->file);
		else if (current->type == TOKEN_REDIR_OUT)
			result = redirect_output(current->file, 0);
		else if (current->type == TOKEN_APPEND)
			result = redirect_output(current->file, 1);
		else if (current->type == TOKEN_HEREDOC)
			result = setup_heredoc(current->file);
		else
			result = 0;
		if (result == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
