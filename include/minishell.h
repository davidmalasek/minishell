/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/07 09:58:28 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#define WORD 0
#define PIPE 1
#define REDIR_OUT 2
#define REDIR_IN 3
#define APPEND_OUT 4
#define HEREDOC 4

#define SUCCESS 0
#define ERROR 1

// environment structure for env linked list
typedef struct s_env
{
	char *key;
	char *value;
	int exported; // 1 if marked with export
	struct s_env *next;
} t_env;

t_env *load_env(char **envp);
char **env_list_to_array(t_env *env);
int add_env_node(t_env **head, char *key, char *value, int exported);

/* PARSING */
typedef struct s_token
{
	char *value;
	int type;
} t_token;

typedef struct s_command
{
	char **args;
	char *infile;
	char *outfile;
	int append;
	int pipe_to_next;
	char *heredoc_delimiter;
} t_command;

// src/parse/utils.c
size_t get_array_length(char **array);
size_t get_token_count(t_token *tokens);
size_t get_command_count(t_token *tokens);

// src/parse/tokenize.c
t_token get_token(char *component);
t_token *tokenize(char *input);

// src/parse/parse.c
t_command *parse(char *input);

/* EXECUTION */
// src/exec/
int exec(t_command *command_list, t_env *env);
char *resolve_path(char *command);
int redir_setup(t_command *command);
int is_parent_builtin(char *str);
int pipe_setup(t_command *command,int pipe_fd[2], int prev_pipe[2]);

// src/builtins/
int ft_cd(char **args, t_env *env);
int ft_echo(char **args);
int ft_env(char **args, t_env *env);
int ft_exit(char **args, int status);
int ft_export(char **args, t_env *env);
int ft_pwd(void);
int ft_unset(char **args, t_env *env);

int arg_count(char **args);
int validate_args(char **args, char *command_name);

#endif