/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/24 11:08:58 by davidmalase      ###   ########.fr       */
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
