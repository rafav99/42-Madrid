/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:29 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	var_values(t_expander *exp, t_env *env, int exit_status)
{
	if (ft_strcmp(exp->var_name, "?") == 0)
		exp->var_value = ft_itoa(exit_status);
	else
		exp->var_value = get_env_value(env, exp->var_name);
	if (!exp->var_value)
		exp->var_value = ft_strdup("");
	if (!exp->var_value)
	{
		free(exp->var_name);
		free(exp->result);
		return (0);
	}
	exp->result = safe_append(exp->result, exp->var_value);
	if (ft_strcmp(exp->var_name, "?") == 0
		|| !get_env_value(env, exp->var_name))
		free(exp->var_value);
	if (!exp->result)
	{
		free(exp->var_name);
		return (0);
	}
	exp->i += exp->var_end;
	free(exp->var_name);
	return (1);
}

static int	var_exp(t_expander *exp, char *str, t_env *env, int exit_status)
{
	exp->i++;
	exp->var_name = get_var_name(str + exp->i, &exp->var_end);
	if (exp->var_name)
	{
		if (!var_values(exp, env, exit_status))
			return (0);
	}
	else if (str[exp->i] == '\0' || ft_isspace(str[exp->i])
		|| str[exp->i] == '\'' || str[exp->i] == '\"')
	{
		exp->result = safe_append(exp->result, "$");
		if (!exp->result)
			return (0);
	}
	else
	{
		exp->result = safe_append(exp->result, "$");
		if (!exp->result)
			return (0);
	}
	return (1);
}

static int	append_char(t_expander *exp, char c)
{
	exp->one_char[0] = c;
	exp->result = safe_append(exp->result, exp->one_char);
	if (!exp->result)
		return (0);
	exp->i++;
	return (1);
}

static int	exp_char(t_expander *exp, char *str, t_env *env, int exit_status)
{
	if (str[exp->i] == '\'' && !exp->double_quotes)
	{
		exp->single_quotes = !exp->single_quotes;
		if (!append_char(exp, str[exp->i]))
			return (0);
	}
	else if (str[exp->i] == '\"' && !exp->single_quotes)
	{
		exp->double_quotes = !exp->double_quotes;
		if (!append_char(exp, str[exp->i]))
			return (0);
	}
	else if (str[exp->i] == '$' && !exp->single_quotes)
	{
		if (!var_exp(exp, str, env, exit_status))
			return (0);
	}
	else
	{
		if (!append_char(exp, str[exp->i]))
			return (0);
	}
	return (1);
}

char	*expand_string(char *str, t_env *env, int exit_status)
{
	t_expander	exp;

	if (!str)
		return (ft_strdup(""));
	exp.result = ft_strdup("");
	if (!exp.result)
		return (NULL);
	exp.i = 0;
	exp.single_quotes = 0;
	exp.double_quotes = 0;
	exp.one_char[1] = '\0';
	while (str[exp.i])
	{
		if (!exp_char(&exp, str, env, exit_status))
			return (NULL);
	}
	return (exp.result);
}
