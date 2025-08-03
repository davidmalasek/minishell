/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:15:00 by tklaus            #+#    #+#             */
/*   Updated: 2025/08/03 19:16:40 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_start_token(char *trimmed)
{
	if (trimmed[0] == '>' || trimmed[0] == '<' || trimmed[0] == '|')
	{
		printf("minishell: syntax error near unexpected token '%c'\n",
			trimmed[0]);
		return (0);
	}
	if ((trimmed[0] == '"' || trimmed[0] == '\'') && ft_strlen(trimmed) == 1)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (0);
	}
	return (1);
}

static int	check_pipe_syntax(char *trimmed)
{
	int	i;
	int	len;
	int	pipe_found;

	i = 0;
	len = ft_strlen(trimmed);
	pipe_found = 0;
	while (i < len)
	{
		if (trimmed[i] == '|')
		{
			if (pipe_found)
				return (printf("minishell: unexpected token '|'\n"), 0);
			pipe_found = 1;
		}
		else if (trimmed[i] != ' ')
			pipe_found = 0;
		i++;
	}
	if (pipe_found)
		return (printf("minishell: unexpected token 'newline'\n"), 0);
	return (1);
}

int	validate_input(char *input)
{
	char	*trimmed;

	if (!input || input[0] == '\0')
		return (0);
	trimmed = input;
	while (*trimmed == ' ')
		trimmed++;
	if (ft_strlen(trimmed) == 0)
		return (0);
	if (!check_start_token(trimmed))
		return (0);
	if (!check_pipe_syntax(trimmed))
		return (0);
	return (1);
}
