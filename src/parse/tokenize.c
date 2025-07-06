/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:43:43 by davidmalase       #+#    #+#             */
/*   Updated: 2025/07/06 10:48:15 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @return Token (PIPE, REDIR_IN, HEREDOC, REDIR_OUT, APPEND_OUT, WORD)
 */
t_token	get_token(char *component)
{
	t_token	token;

	if (ft_strcmp(component, "|") == 0)
		token.type = PIPE;
	else if (ft_strcmp(component, "<") == 0)
		token.type = REDIR_IN;
	else if (ft_strcmp(component, "<<") == 0)
		token.type = HEREDOC;
	else if (ft_strcmp(component, ">") == 0)
		token.type = REDIR_OUT;
	else if (ft_strcmp(component, ">>") == 0)
		token.type = APPEND_OUT;
	else
		token.type = WORD;
	token.value = ft_strdup(component);
	return (token);
}
/**
 * @return Array of tokens
 */
t_token	*tokenize(char *input)
{
	char	**input_split;
	t_token	*tokens;
	size_t	components_count;
	size_t	i;
	i=0;

	input_split = ft_split(input, ' ');
	if (!input_split)
		return (NULL);
	components_count = get_array_length(input_split);
	tokens = malloc(sizeof(t_token) * (components_count + 1));
	if (!tokens)
		return (NULL);
	while (i < components_count)
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
