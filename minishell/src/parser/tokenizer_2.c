/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:06:50 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 20:06:58 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_loop(char *input, int *i, int len, t_quote_state *qs)
{
	while (*i < len)
	{
		if (is_quote(input[*i]))
		{
			if (!qs->in_quotes)
			{
				qs->in_quotes = 1;
				qs->quote_type = input[*i];
			}
			else if (qs->in_quotes && input[*i] == qs->quote_type)
			{
				qs->in_quotes = 0;
				qs->quote_type = 0;
			}
		}
		if (!qs->in_quotes && (is_whitespace(input[*i])
				|| is_metachar(input[*i])))
			break ;
		(*i)++;
	}
}

int	process_token(char *input, int *i, int len, t_token **tokens)
{
	if (is_metachar(input[*i]))
	{
		if (!h_metachar(input, i, len, tokens))
			return (0);
	}
	else
	{
		if (!h_word(input, i, len, tokens))
			return (0);
	}
	return (1);
}
