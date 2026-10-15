/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_sign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:28:06 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 17:32:55 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	append_var_sign(char **res, int *i)
{
	char	*tmp;

	tmp = safe_append(*res, "$");
	if (!tmp)
	{
		free(*res);
		*res = NULL;
		return (-1);
	}
	*res = tmp;
	(*i)++;
	return (0);
}

int	append_value(char **res, char *val)
{
	char	*tmp;

	tmp = safe_append(*res, val);
	free(val);
	if (!tmp)
	{
		free(*res);
		*res = NULL;
		return (-1);
	}
	*res = tmp;
	return (0);
}

int	status_var_sign(char *str, t_env *env, char **res, int *i)
{
	char	*val;

	if (str[*i] == '?')
	{
		val = ft_itoa(env->last_status);
		if (!val || append_value(res, val) == -1)
			return (-1);
		(*i)++;
		return (1);
	}
	return (0);
}
