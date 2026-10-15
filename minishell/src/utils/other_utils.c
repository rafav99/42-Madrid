/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:01 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_quotes(int *in_quotes, char const *s, int i)
{
	if (s[i] == '\'' || s[i] == '"')
	{
		if (*in_quotes == 0)
			*in_quotes = s[i];
		else if (*in_quotes == s[i])
			*in_quotes = 0;
	}
}

int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;
	int	in_quotes;
	int	i;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	i = 0;
	while (s[i])
	{
		check_quotes(&in_quotes, s, i);
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if ((s[i] == c && !in_quotes) && in_word)
			in_word = 0;
		i++;
	}
	return (count);
}
