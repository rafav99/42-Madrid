/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:35 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 19:02:16 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	valid_pipe_syntax(t_token *tokens)
{
	t_token	*previous;

	previous = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE && (!previous
				|| previous->type == TOKEN_PIPE || !tokens->next
				|| tokens->next->type == TOKEN_PIPE))
		{
			print_syntax_error("unexpected pipe");
			return (0);
		}
		previous = tokens;
		tokens = tokens->next;
	}
	return (1);
}

t_command	*parse_input(char *input, t_env **g_env)
{
	t_token		*tokens;
	t_command	*commands;

	if (!input || !*input)
		return (NULL);
	tokens = tokenize(input);
	if (!tokens)
	{
		(*g_env)->last_status = 2;
		return (NULL);
	}
	if (!valid_pipe_syntax(tokens))
	{
		free_tokens(tokens);
		(*g_env)->last_status = 2;
		return (NULL);
	}
	expand_variables(tokens, *g_env);
	commands = build_commands(tokens);
	if (!commands)
		(*g_env)->last_status = 2;
	free_tokens(tokens);
	return (commands);
}

void	free_command(t_command *cmd)
{
	t_command	*next;
	t_redir		*redir;
	t_redir		*next_redir;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
			free_array(cmd->args);
		redir = cmd->redirects;
		while (redir)
		{
			next_redir = redir->next;
			if (redir->file)
				free(redir->file);
			free(redir);
			redir = next_redir;
		}
		free(cmd);
		cmd = next;
	}
}

t_command	*create_new_command(void)
{
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}

static char	echo_char(char c, int *in_quotes, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		if (!*in_quotes)
		{
			*in_quotes = 1;
			*quote_char = c;
			return (0);
		}
		else if (c == *quote_char)
		{
			*in_quotes = 0;
			*quote_char = 0;
			return (0);
		}
	}
	return (1);
}

char	*process_echo_word(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;

	if (!str)
		return (NULL);
	result = ft_malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quotes = 0;
	quote_char = 0;
	while (str[i])
	{
		if (echo_char(str[i], &in_quotes, &quote_char))
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
