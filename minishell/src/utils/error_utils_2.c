/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:50 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd_not_found(const char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd);
}

void	print_shell_error(const char *context, const char *message)
{
	if (!message)
		ft_dprintf(STDERR_FILENO, "%s\n", context);
	else
		ft_dprintf(STDERR_FILENO, "%s: %s\n", context, message);
}

void	print_syntax_error(const char *message)
{
	ft_dprintf(STDERR_FILENO, "syntax error: %s\n", message);
}
