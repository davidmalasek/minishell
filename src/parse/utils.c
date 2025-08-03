/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/03 18:29:47 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	get_token_count(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens[count].type != -1)
	{
		count++;
	}
	return (count);
}

size_t	get_command_count(t_token *tokens)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (tokens[i].type != -1)
	{
		if (tokens[i].type == PIPE)
			count++;
		i++;
	}
	return (count + 1);
}

size_t	get_array_length(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
	{
		len++;
	}
	return (len);
}

size_t	operator_token_length(const char *start, char *quote_char_out)
{
	if ((start[0] == '<' && start[1] == '<') || (start[0] == '>'
			&& start[1] == '>'))
	{
		*quote_char_out = 0;
		return (2);
	}
	else
	{
		*quote_char_out = 0;
		return (1);
	}
}
