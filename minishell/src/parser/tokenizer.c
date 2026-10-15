/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:07:13 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 20:07:14 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*next;

	while (tokens)
	{
		next = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = next;
	}
}

static int	create_single_metachar(char *input, int *i, t_token **tokens)
{
	char	*value;
	t_token	*new_tok;

	value = ft_substr(input, *i, 1);
	if (input[*i] == '|')
		new_tok = create_token(value, TOKEN_PIPE);
	else if (input[*i] == '<')
		new_tok = create_token(value, TOKEN_REDIR_IN);
	else
		new_tok = create_token(value, TOKEN_REDIR_OUT);
	*i += 1;
	if (!new_tok || !value)
		return (0);
	add_token_back(tokens, new_tok);
	return (1);
}

int	h_metachar(char *input, int *i, int len, t_token **tokens)
{
	int		start;
	char	*value;
	t_token	*new_tok;

	start = *i;
	if (input[*i] == '<' && *i + 1 < len && input[*i + 1] == '<')
	{
		value = ft_substr(input, start, 2);
		new_tok = create_token(value, TOKEN_HEREDOC);
		*i += 2;
	}
	else if (input[*i] == '>' && *i + 1 < len && input[*i + 1] == '>')
	{
		value = ft_substr(input, start, 2);
		new_tok = create_token(value, TOKEN_APPEND);
		*i += 2;
	}
	else
		return (create_single_metachar(input, i, tokens));
	if (!new_tok || !value)
		return (0);
	add_token_back(tokens, new_tok);
	return (1);
}

int	h_word(char *input, int *i, int len, t_token **tokens)
{
	int				start;
	t_quote_state	qs;
	char			*value;
	t_token			*new_tok;

	start = *i;
	qs.in_quotes = 0;
	qs.quote_type = 0;
	parse_loop(input, i, len, &qs);
	if (qs.in_quotes)
	{
		print_syntax_error("unclosed quotation mark");
		return (0);
	}
	value = ft_substr(input, start, *i - start);
	new_tok = create_token(value, TOKEN_WORD);
	if (!new_tok || !value)
		return (0);
	add_token_back(tokens, new_tok);
	return (1);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;
	int		len;

	tokens = NULL;
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		while (i < len && is_whitespace(input[i]))
			i++;
		if (i >= len)
			break ;
		if (!process_token(input, &i, len, &tokens))
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
