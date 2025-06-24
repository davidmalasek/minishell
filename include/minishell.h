/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:31:41 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/24 17:44:08 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
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
# define HEREDOC 4

// PARSING
typedef struct s_token
{
	char *value; // The actual text (e.g. "ls", "|", "file.txt")
	int type;    // Type of token: WORD, PIPE, REDIR_IN, REDIR_OUT, etc.
}		t_token;

typedef struct s_command
{
	char **args;      // List of arguments for execve (e.g. {"ls", "-l", NULL})
	char *infile;     // File for input redirection (if any)
	char *outfile;    // File for output redirection (if any)
	int append;       // 1 if >> was used, 0 if > was used
	int pipe_to_next; // 1 if this command pipes to next, 0 otherwise
}		t_command;

// src/parse/utils.c
size_t	get_array_length(char **array);
size_t	get_token_count(t_token *tokens);
size_t	get_command_count(t_token *tokens);

// src/parse/tokenize.c
t_token	get_token(char *component);
t_token	*tokenize(char *input);

#endif