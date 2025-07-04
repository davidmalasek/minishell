/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:31:41 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/22 13:25:15 by tomasklaus       ###   ########.fr       */
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
}	t_token;

typedef struct s_command
{
	char **args;      // List of arguments for execve (e.g. {"ls", "-l", NULL})
	char *infile;     // File for input redirection (if any)
	char *outfile;    // File for output redirection (if any)
	int append;       // 1 if >> was used, 0 if > was used
	int pipe_to_next; // 1 if this command pipes to next, 0 otherwise
}	t_command;

/* exec.c */
void exec(t_command *command);

#endif