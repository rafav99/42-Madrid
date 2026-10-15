/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:23 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	backup_std_fds(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
	{
		print_error("dup", "Failed to backup stdio");
		if (*stdin_backup != -1)
			close(*stdin_backup);
		if (*stdout_backup != -1)
			close(*stdout_backup);
		return (-1);
	}
	return (0);
}

static void	restore_std_fds(int *stdin_backup, int *stdout_backup)
{
	if (*stdin_backup != -1)
		dup2(*stdin_backup, STDIN_FILENO);
	if (*stdout_backup != -1)
		dup2(*stdout_backup, STDOUT_FILENO);
	if (*stdin_backup != -1)
		close(*stdin_backup);
	if (*stdout_backup != -1)
		close(*stdout_backup);
}

int	h_redirections(t_command *cmd, int *stdin_backup, int *stdout_bp)
{
	int	redir_status;

	if (backup_std_fds(stdin_backup, stdout_bp) == -1)
		return (-1);
	redir_status = setup_redirections(cmd->redirects);
	if (redir_status == -1)
		restore_std_fds(stdin_backup, stdout_bp);
	return (redir_status);
}
