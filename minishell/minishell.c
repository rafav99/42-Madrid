/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:10 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 19:03:14 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		g_signal;

void	init_shell(char **envp, t_env **g_env)
{
	*g_env = init_env(envp);
	if (!*g_env)
		exit(EXIT_FAILURE);
	setup_signals();
	g_signal = 0;
}

void	run_shell(t_env **g_env)
{
	char		*input;
	t_command	*cmd;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (*input)
		{
			add_history(input);
			cmd = parse_input(input, g_env);
			if (cmd)
			{
				execute_commands(cmd, *g_env);
				free_command(cmd);
			}
		}
		free(input);
	}
}

void	cleanup_shell(t_env **g_env)
{
	free_env(*g_env);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*g_env;
	int		last_status;

	(void)argc;
	(void)argv;
	init_shell(envp, &g_env);
	run_shell(&g_env);
	last_status = g_env->last_status;
	cleanup_shell(&g_env);
	return (last_status);
}
