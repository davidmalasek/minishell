/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/22 14:56:41 by dmalasek         ###   ########.fr       */
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

t_token	*tokenize(char *input)
{
	char	**input_split;
	t_token	*tokens;
	size_t	count;
	size_t	i;

	input_split = ft_split(input, ' ');
	if (!input_split)
		return (NULL);
	count = get_array_length(input_split);
	tokens = malloc(sizeof(t_token) * (count + 1));
	if (!tokens)
		return (NULL);
	while (i < count)
	{
		tokens[i] = get_token(input_split[i]);
		free(input_split[i]);
		i++;
	}
	tokens[i].value = NULL;
	tokens[i].type = -1;
	free(input_split);
	return (tokens);
}

t_command	*parse(char *input)
{
	t_token	*tokens;

	tokens = tokenize(input);
	if (!tokens)
		return (NULL);
}

/*
DAVID TODO:
- parsovani
- history
*/
