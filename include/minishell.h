/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/07/04 12:38:22 by tomasklaus       ###   ########.fr       */
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
	char	*value;
	int		type;
}			t_token;

typedef struct s_command
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
	int		pipe_to_next;
	char	*heredoc_delimiter;
}			t_command;

// src/parse/utils.c
size_t		get_array_length(char **array);
size_t		get_token_count(t_token *tokens);
size_t		get_command_count(t_token *tokens);

// src/parse/tokenize.c
t_token		get_token(char *component);
t_token		*tokenize(char *input);

#endif