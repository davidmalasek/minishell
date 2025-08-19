/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 14:39:37 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/19 16:51:24 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define WORD 0
# define PIPE 1
# define REDIR_OUT 2
# define REDIR_IN 3
# define APPEND_OUT 4
# define HEREDOC 5

# define SUCCESS 0
# define ERROR 1

// environment structure for env linked list

typedef struct s_env
{
	char					*key;
	char					*value;
	int						exported;
	struct s_env			*next;
}							t_env;

t_env						*load_env(char **envp);
char						**env_list_to_array(t_env *env);
int							add_env_node(t_env **head, char *key, char *value,
								int exported);
char						*ft_strjoin3(char const *s1, char const *s2,
								char const *s3);
int							setup_signal_handlers(void);
void						sigint_handler(int signo);
void						sigint_handler_child(int signo);

/* PARSING */
typedef struct s_token
{
	char					*value;
	int						type;
}							t_token;

typedef struct s_outfile_node
{
	char					*filename;
	struct s_outfile_node	*next;
}							t_outfile_node;

typedef struct s_command
{
	char					**args;
	char					*infile;
	char					*outfile;
	int						append;
	int						pipe_to_next;
	char					*heredoc_delim;
	int						has_quotes;
	t_outfile_node			*outfile_old;
	t_outfile_node			*infile_old;
	t_outfile_node			*heredoc_old;
}							t_command;

typedef struct s_exec_context
{
	t_command				*command_list;
	t_env					**env;
}							t_exec_context;

// src/main.c
t_env						*initialize_shell(char **envp);
char						*get_input(t_env *env);
int							validate_input(char *input);
int							handle_empty_or_signal(char *input, int *status);
int							handle_invalid_input(char *input, int *status);

int							validate_input(char *input);

// src/main_utils_2.c
int							has_invalid_pipe_sequence(char *input);
int							needs_continuation(char *input);
char						*get_continuation_input(char *initial_input);

// src/main_utils_3.c
char						*get_continuation_input(char *initial_input);

// src/parse/utils.c
size_t						get_array_length(char **array);
size_t						get_token_count(t_token *tokens);
size_t						get_command_count(t_token *tokens);
size_t						operator_token_length(const char *start,
								char *quote_char_out);

// src/parse/tokenize.c
t_token						process_token(char *component, t_env *env,
								int last_exit_status);
t_token						*tokenize(char *input, t_env *env,
								int last_exit_status, int *has_quotes);
char						*expand_in_double_quotes(char *component,
								t_env *env, int last_exit_status);

// src/parse/parse.c
t_command					*parse(char *input, t_env *env,
								int *last_exit_status);

// src/parse/preprocess.c
char						**custom_split(const char *input, char delimiter,
								int *has_quotes);
int							is_delimiter(char character, char delimiter);
size_t						scan_token_length(const char *start, char delimiter,
								int *has_quotes, char *quote_char_out);
char						*alloc_and_copy_token(const char *start,
								size_t length);

/* EXECUTION */
// src/exec/
int							exec(t_command *command_list, t_env **env,
								int *status);
char						*resolve_path(char *command, t_env *env);
int							redir_setup(t_command *command, t_env *env);
int							is_parent_builtin(t_command *command);
int							pipe_setup(t_command *command, int pipe_fd[2],
								int prev_pipe[2]);
int							is_builtin(char *str);
void						free_str_array(char **arr);
int							heredoc_loop(t_outfile_node *curr, int pipe_fd[2]);

// src/builtins/
int							ft_cd(char **args, t_env *env);
int							ft_echo(char **args);
int							ft_env(char **args, t_env *env);
int							ft_exit(char **args, int status,
								t_exec_context exec_context);
int							ft_export(char **args, t_env *env);
int							ft_pwd(void);
int							ft_unset(char **args, t_env **env);

int							arg_count(char **args);
int							validate_args(char **args, char *command_name,
								int max_args, int min_args);
int							is_valid_identifier(char *key);

// src/cleanup/
void						cleanup_env(t_env *env);
void						cleanup_commands(t_command *command_list);
void						exit_shell(t_command *command_list, t_env *env,
								int exit_code);
void						cleanup_tokens(t_token *tokens);
void						cleanup_file_list(t_outfile_node *list);
void						cleanup_single_command(t_command *cmd);

// src/parse/preprocess_utils.c
char						*get_token(const char **cursor, char delimiter,
								int *has_quotes);
size_t						count_tokens(const char *input, char delimiter,
								int *has_quotes);
char						**fill_tokens(const char *input, char delimiter,
								int *has_quotes, size_t token_count);
int							is_delimiter(char character, char delimiter);
int							is_operator(const char *s);

// src/parse/tokenize_utils.c
char						*get_env_value(t_env *env, char *key);
char						*expand_variable(char *token, t_env *env,
								int last_exit_status);
int							is_single_quoted(char *component);
char						*remove_quotes(char *component);
int							is_double_quoted(char *component);

// src/parse/tokenize_utils_2.c
char						*extract_quoted_content(char *component);
char						*handle_simple_exit_status(char *content,
								int last_exit_status);
char						*handle_exit_status_with_context(char *content,
								char *dollar_pos, int last_exit_status);
char						*find_variable_end(char *var_start);
char						*build_result_from_parts(char *before,
								char *var_value, char *var_end, char *var_name);

// src/parse/tokenize_utils_3.c
int							get_operator_token_type(char *component);
char						*handle_single_quoted(char *component);
char						*handle_double_quoted(char *component, t_env *env,
								int last_exit_status);
char						*handle_variable_component(char *component,
								t_env *env, int last_exit_status);
char						*process_word_token(char *component, t_env *env,
								int last_exit_status);

// src/parse/parse_utils.c
int							handle_redir_out(t_command *cmd, t_token *tokens,
								size_t *tkn_index);
int							handle_append_out(t_command *cmd, t_token *tokens,
								size_t *tkn_index);
int							handle_redir_in(t_command *cmd, t_token *tokens,
								size_t *tkn_index);
int							handle_heredoc(t_command *cmd, t_token *tokens,
								size_t *tkn_index);
int							handle_token(t_command *cmd, t_token *tokens,
								size_t *tkn_index, size_t *arg_index);

// src/parse/parse_utils_2.c
void						init_command(t_command *command);
size_t						count_args(t_token *tokens, size_t index);
void						free_commands(t_command *commands, size_t count);
int							fill_command_fields(t_command *cmd, t_token *tokens,
								size_t *tkn_index);
void						free_and_set(char **target, char *new_value);
int							check_output_old(t_command *cmd, char *value);
void						all_infiles(t_command *cmd, char *value);
void						all_heredocs(t_command *cmd, char *value);

// src/exec/exec_utils.c
void						setup_pipes(int pipes[4]);
int							child_setup(t_command *cmd, t_env *env,
								int pipes[4]);
int							is_parent_builtin(t_command *command);
int							exec_builtin(t_command command, t_env **env,
								int status, t_exec_context exec_context);
void						no_command(t_command *cmd,
								t_exec_context exec_context, t_env *env,
								char *path);

// Define the global variable for signal interruption
extern int					g_signal_interrupted;

#endif