/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:37 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fill_args_copy(t_command *cmd, char **new_args, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	return (count);
}

static char	**prep_args(t_command *cmd, char *arg_val, char **p_arg)
{
	int		count;
	char	**new_args;
	int		is_echo_arg;

	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	is_echo_arg = (count == 0 && !ft_strcmp(arg_val, "echo"))
		|| (count > 0 && !ft_strcmp(cmd->args[0], "echo"));
	new_args = (char **)ft_malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (NULL);
	fill_args_copy(cmd, new_args, count);
	if (is_echo_arg && count > 0)
		*p_arg = process_echo_word(arg_val);
	else
		*p_arg = process_cmd_word(arg_val);
	if (!*p_arg)
	{
		free(new_args);
		return (NULL);
	}
	new_args[count + 1] = NULL;
	return (new_args);
}

int	add_argument(t_command *cmd, char *arg_val)
{
	char	**new_args;
	char	*processed_arg;
	int		count;

	new_args = prep_args(cmd, arg_val, &processed_arg);
	if (!new_args)
		return (-1);
	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	new_args[count] = processed_arg;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
	return (0);
}

void	add_redir_back(t_redir **list, t_redir *new_redir)
{
	t_redir	*current;

	if (!list || !new_redir)
		return ;
	if (!*list)
		*list = new_redir;
	else
	{
		current = *list;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

t_redir	*create_redir(int type, char *filename)
{
	t_redir	*redir;
	char	*processed_file;

	redir = (t_redir *)ft_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	processed_file = process_cmd_word(filename);
	if (!processed_file)
	{
		free(redir);
		return (NULL);
	}
	redir->file = processed_file;
	redir->next = NULL;
	return (redir);
}
