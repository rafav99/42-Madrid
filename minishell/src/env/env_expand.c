/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:58 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	manage_envar(char *str, t_env *env, char **res, int *i)
{
	char	*name;
	char	*val;
	int		j;

	j = 0;
	while ((str[*i + j] >= 'a' && str[*i + j] <= 'z')
		|| (str[*i + j] >= 'A' && str[*i + j] <= 'Z')
		|| (str[*i + j] >= '0' && str[*i + j] <= '9')
		|| str[*i + j] == '_')
		j++;
	name = ft_substr(str, *i, j);
	if (!name)
		return (free(*res), -1);
	val = ft_strdup(get_env_value(env, name));
	free(name);
	if (val && append_value(res, val) == -1)
		return (-1);
	*i += j;
	return (1);
}

static int	process_char(char *str, t_env *env, int *i, char **res)
{
	int	handled;

	handled = status_var_sign(str, env, res, i);
	if (handled)
	{
		if (handled == -1)
			return (-1);
		return (0);
	}
	if ((str[*i] >= 'a' && str[*i] <= 'z')
		|| (str[*i] >= 'A' && str[*i] <= 'Z') || str[*i] == '_')
	{
		if (manage_envar(str, env, res, i) == -1)
			return (-1);
		return (0);
	}
	return (append_var_sign(res, i));
}

static int	quotes_n_var(char *str, t_env *env, int *i, char **res)
{
	static int	sq = 0;
	static int	dq = 0;

	if (str[*i] == '\'' && !dq)
		sq = !sq;
	else if (str[*i] == '"' && !sq)
		dq = !dq;
	else if (str[*i] == '$' && !sq)
	{
		(*i)++;
		if (process_char(str, env, i, res) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

char	*expand_env_variables(char *str, t_env *env)
{
	int		i;
	char	*res;
	char	tmp[2];
	int		ret;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ret = quotes_n_var(str, env, &i, &res);
		if (ret == -1)
			return (NULL);
		if (ret == 1)
			continue ;
		tmp[0] = str[i++];
		tmp[1] = '\0';
		res = safe_append(res, tmp);
		if (!res)
			return (NULL);
	}
	return (res);
}
