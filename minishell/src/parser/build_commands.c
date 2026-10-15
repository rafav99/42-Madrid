/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:27 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_word_token(t_command *current_cmd,
	t_token **current_tok_ptr)
{
	t_token	*current_tok;

	current_tok = *current_tok_ptr;
	if (!current_tok->value || !*current_tok->value)
	{
		*current_tok_ptr = current_tok->next;
		return (1);
	}
	if (add_argument(current_cmd, current_tok->value) == -1)
		return (0);
	*current_tok_ptr = current_tok->next;
	return (1);
}

static int	handle_pipe_token(t_command **current_cmd,
	t_token **current_tok_ptr, t_command **head)
{
	t_command	*next_cmd;

	next_cmd = create_new_command();
	if (!next_cmd)
	{
		free_command(*head);
		return (0);
	}
	(*current_cmd)->next = next_cmd;
	*current_cmd = next_cmd;
	*current_tok_ptr = (*current_tok_ptr)->next;
	return (1);
}

static int	handle_redirection_token(t_command *current_cmd,
	t_token **current_tok_ptr, t_command *head)
{
	int		redir_type;
	t_redir	*new_redir;
	t_token	*current_tok;

	current_tok = *current_tok_ptr;
	redir_type = current_tok->type;
	current_tok = current_tok->next;
	if (!current_tok || current_tok->type != TOKEN_WORD || !current_tok->value)
	{
		print_syntax_error("missing filename after redirection");
		free_command(head);
		return (0);
	}
	new_redir = create_redir(redir_type, current_tok->value);
	if (!new_redir)
	{
		free_command(head);
		return (0);
	}
	add_redir_back(&(current_cmd->redirects), new_redir);
	*current_tok_ptr = current_tok->next;
	return (1);
}

static int	handle_token_type(t_command **current_cmd,
	t_token **current_tok, t_command **head)
{
	if ((*current_tok)->type == TOKEN_WORD)
	{
		if (!handle_word_token(*current_cmd, current_tok))
			return (0);
	}
	else if ((*current_tok)->type == TOKEN_PIPE)
	{
		if (!handle_pipe_token(current_cmd, current_tok, head))
			return (0);
	}
	else if ((*current_tok)->type >= TOKEN_REDIR_IN
		&& (*current_tok)->type <= TOKEN_APPEND)
	{
		if (!handle_redirection_token(*current_cmd, current_tok, *head))
			return (0);
	}
	else
	{
		print_syntax_error("unexpected token type");
		free_command(*head);
		return (0);
	}
	return (1);
}

t_command	*build_commands(t_token *tokens)
{
	t_command	*head;
	t_command	*current_cmd;
	t_token		*current_tok;

	if (!tokens)
		return (NULL);
	head = create_new_command();
	if (!head)
		return (NULL);
	current_cmd = head;
	current_tok = tokens;
	while (current_tok)
	{
		if (!handle_token_type(&current_cmd, &current_tok, &head))
			return (NULL);
	}
	return (head);
}
