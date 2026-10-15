/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:54 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	word_length(char const *s, char c)
{
	int	len;
	int	in_quotes;

	len = 0;
	in_quotes = 0;
	while (s[len])
	{
		if (s[len] == '\'' || s[len] == '"')
		{
			if (!in_quotes)
				in_quotes = s[len];
			else if (in_quotes == s[len])
				in_quotes = 0;
		}
		if (s[len] == c && !in_quotes)
			break ;
		len++;
	}
	return (len);
}

static void	word_copy(char *dst, char const *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static void	free_split(char **split, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	reserve_result(char **result, int word_len, int i)
{
	result[i] = (char *)ft_malloc(sizeof(char) * (word_len + 1));
	if (!result[i])
	{
		free_split(result, i);
		return (0);
	}
	return (1);
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		word_len;
	int		i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)ft_malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		while (*s == c)
			s++;
		word_len = word_length(s, c);
		if (reserve_result(result, word_len, i) == 0)
			return (NULL);
		word_copy(result[i], s, word_len);
		s += word_len;
		i++;
	}
	result[i] = NULL;
	return (result);
}
