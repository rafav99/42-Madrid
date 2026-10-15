/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:35 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 18:29:32 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

typedef struct s_env		t_env;
typedef struct s_command	t_command;
typedef struct s_redir		t_redir;
typedef struct s_pipeline	t_pipeline;
typedef struct s_pipes		t_pipes;

/* Estructuras internas para la ejecución */
typedef struct s_process
{
	pid_t					pid;
	int						status;
}							t_process;

typedef struct s_pipeline
{
	int						cmd_index;
	int						last_status;
	int						fd_in;
	int						is_last;
}							t_pipeline;

typedef struct s_pipes
{
	t_pipeline				pl;
	pid_t					*pids;
}							t_pipes;

/* Funciones principales del ejecutor */
int							execute_commands(t_command *cmd, t_env *env);
int							execute_simple_command(t_command *cmd, t_env *env);
int							execute_pipeline(t_command *cmd, t_env *env);
void						ex_pl_command(t_command *cmd, t_env *env, int fd_in,
								int fd_out[2]);
int							execute_external_child(t_command *cmd, t_env *env);
int							count_commands(t_command *cmd_list);
int							wait_child(pid_t *pids, int num_cmds,
								t_command *cmd_list);
int							check_brk_pipe(t_command *cmd_list);
int							h_redirections(t_command *cmd, int *stdin_backup,
								int *stdout_bp);

/* Funciones de ejecución de comandos */
int							is_builtin(char *cmd);
int							execute_builtin(t_command *cmd, t_env *env);
int							execute_external(t_command *cmd, t_env *env);
char						*find_command_path(char *cmd, t_env *env);

/* Funciones para manejo de redirecciones */
int							setup_redirections(t_redir *redirects);
int							redirect_output(char *file, int append);
int							setup_heredoc(char *delimiter);

/* Funciones para manejo de pipes */
int							create_pipes(int pipes[2][2], int cmd_count);
void						close_pipes(int pipes[2][2], int cmd_count);
void						setup_pipe_fds(int pipes[2][2], int i,
								int cmd_count);

#endif