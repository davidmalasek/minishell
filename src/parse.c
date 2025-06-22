/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/22 12:52:39 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	get_token(char *chunk)
{
	t_token	token;

	if (ft_strcmp(chunk, "|") == 0)
		token.type = PIPE;
	else if (ft_strcmp(chunk, "<") == 0)
		token.type = REDIR_IN;
	else if (ft_strcmp(chunk, "<<") == 0)
		token.type = HEREDOC;
	else if (ft_strcmp(chunk, ">") == 0)
		token.type = REDIR_OUT;
	else if (ft_strcmp(chunk, ">>") == 0)
		token.type = APPEND_OUT;
	else
		token.type = WORD;
	token.value = ft_strdup(chunk);
	return (token);
}

t_token	tokenize(char *input)
{
	char	**input_split;
	int		i;
	int		e;

	input_split = ft_split(input, ' ');
	i = 0;
	while (input_split[i] != '\0')
	{
		e = 0;
		while (input_split[i][e] != '\0')
		{
		}
	}
}

t_command	parse(char *input)
{
	t_token	tokenized_input;

	tokenized_input = tokenize(input);
}

/*
DAVID TODO:
- parsovani
- history
*/
