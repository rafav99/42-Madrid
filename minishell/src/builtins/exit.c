/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:27:48 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 19:00:57 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static void	check_sign(char c, int *sign, int *i)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*sign = -1;
		else
			*sign = 1;
		*i = *i + 1;
	}
}

static long	ft_strtol(const char *str, char **endptr, int base)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (is_space(str[i]) || str[i] == '"' || str[i] == '\''))
		i++;
	check_sign(str[i], &sign, &i);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * base + (str[i] - '0');
		else if (str[i] != '"' && str[i] != '\'' && !is_space(str[i]))
			break ;
		i++;
	}
	if (endptr)
		*endptr = (char *)str + i;
	return (sign * result);
}

static int	is_valid_number(const char *str, long *result)
{
	char	*endptr;
	long	num;

	while (*str && (is_space(*str) || *str == '"' || *str == '\''))
		str++;
	if (!*str)
		return (0);
	num = ft_strtol(str, &endptr, 10);
	while (*endptr && (is_space(*endptr) || *endptr == '"' || *endptr == '\''))
		endptr++;
	if (*endptr)
		return (0);
	*result = num;
	return (1);
}

int	builtin_exit(t_command *cmd, t_env *env)
{
	long	status;

	write(STDOUT_FILENO, "exit\n", 5);
	if (!cmd->args[1])
	{
		status = env->last_status;
		cleanup_shell(&env);
		exit(status);
	}
	if (!is_valid_number(cmd->args[1], &status))
	{
		print_error("exit", "numeric argument required");
		cleanup_shell(&env);
		exit(2);
	}
	if (cmd->args[2])
	{
		print_error("exit", "too many arguments");
		return (1);
	}
	cleanup_shell(&env);
	exit(status & 255);
}
