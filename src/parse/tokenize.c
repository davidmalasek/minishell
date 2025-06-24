/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:43:43 by davidmalase       #+#    #+#             */
/*   Updated: 2025/06/24 17:34:56 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_token	*tokenize(char *input)
{
	char	**input_split;
	t_token	*tokens;
	size_t	components_count;
	size_t	i;

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
