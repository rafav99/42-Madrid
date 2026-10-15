/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osmunoz- <osmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:29:39 by osmunoz-          #+#    #+#             */
/*   Updated: 2025/07/20 20:06:01 by osmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* Tipos de token */
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_HEREDOC 5
# define TOKEN_APPEND 6

/* Estructura de token */
typedef struct s_token
{
	char				*value;
	int					type;
	struct s_token		*next;
}						t_token;

/* Estructura de redirección */
typedef struct s_redir
{
	int					type;
	char				*file;
	struct s_redir		*next;
}						t_redir;

/* Estructura de comando */
typedef struct s_command
{
	char				**args;
	t_redir				*redirects;
	struct s_command	*next;
}						t_command;

typedef struct s_quote_state
{
	int					in_quotes;
	char				quote_type;
}						t_quote_state;

typedef struct s_expander
{
	int					i;
	int					single_quotes;
	int					double_quotes;
	int					var_end;
	char				one_char[2];
	char				*var_name;
	char				*var_value;
	char				*result;
}						t_expander;

/* Funciones de tokenización */
t_token					*tokenize(char *input);
void					free_tokens(t_token *tokens);

/* Funciones de expansión */
void					expand_variables(t_token *tokens, t_env *env);
char					*get_var_name(char *str, int *end);
char					*expand_string(char *str, t_env *env, int exit_status);

/* Funciones de parsing */
t_command				*parse_input(char *input, t_env **g_env);
t_command				*build_commands(t_token *tokens);
void					free_command(t_command *cmd);
int						is_redirection_token(t_token *token);
char					*ft_strncpy(char *dst, const char *src, size_t n);
int						is_redirection_token(t_token *token);
t_command				*create_new_command(void);
char					*process_echo_word(char *str);
t_redir					*create_redir(int type, char *filename);
void					add_redir_back(t_redir **list, t_redir *new_redir);
int						add_argument(t_command *cmd, char *arg_val);
int						is_whitespace(char c);
int						is_metachar(char c);
int						is_quote(char c);
void					add_token_back(t_token **list, t_token *new_token);
t_token					*create_token(char *value, int type);
char					*process_cmd_word(char *str);
int						h_word(char *input, int *i, int len, t_token **tokens);
int						h_metachar(char *input, int *i, int len,
							t_token **tokens);
int						process_token(char *input, int *i, int len,
							t_token **tokens);
void					parse_loop(char *input, int *i, int len,
							t_quote_state *qs);

#endif