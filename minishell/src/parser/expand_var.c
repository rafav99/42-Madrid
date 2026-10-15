/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:31 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_token_value(t_token *current, t_env *env, int last_status)
{
	char	*expanded;

	expanded = expand_string(current->value, env, last_status);
	if (expanded)
	{
		free(current->value);
		current->value = expanded;
	}
}

static t_token	*empty(t_token *tokens, t_token *prev,
	t_token *current, t_token *next)
{
	if (!*current->value && !is_redirection_token(prev)
		&& !is_redirection_token(next))
	{
		if (!prev && next)
			tokens = next;
		else if (prev)
			prev->next = next;
		else
		{
			current->value = ft_strdup("");
			if (!current->value)
				current->value = ft_strdup("");
		}
	}
	return (tokens);
}

void	expand_variables(t_token *tokens, t_env *env)
{
	t_token	*current;
	t_token	*next;
	t_token	*prev;
	int		last_status;

	if (!tokens)
		return ;
	if (env)
		last_status = env->last_status;
	else
		last_status = 0;
	current = tokens;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
		{
			update_token_value(current, env, last_status);
			tokens = empty(tokens, prev, current, next);
		}
		prev = current;
		current = next;
	}
}
