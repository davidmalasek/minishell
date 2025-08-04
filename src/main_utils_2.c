/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:15:00 by tklaus            #+#    #+#             */
/*   Updated: 2025/08/04 09:58:49 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_start_token(char *trimmed)
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

int	check_pipe_syntax(char *trimmed)
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
				return (printf("minishell: syntax error: unexpected token\n"),
					0);
			pipe_found = 1;
		}
		else if (trimmed[i] != ' ' && trimmed[i] != '\t')
			pipe_found = 0;
		i++;
	}
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

int	has_invalid_pipe_sequence(char *input)
{
	int	i;
	int	pipe_found;

	i = 0;
	pipe_found = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (pipe_found)
				return (1);
			pipe_found = 1;
		}
		else if (input[i] != ' ' && input[i] != '\t')
			pipe_found = 0;
		i++;
	}
	return (0);
}

int	needs_continuation(char *input)
{
	char	*trimmed;
	int		len;

	if (!input)
		return (0);
	if (has_invalid_pipe_sequence(input))
		return (0);
	trimmed = input;
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (trimmed[0] == '|' || trimmed[0] == '>' || trimmed[0] == '<')
		return (0);
	len = ft_strlen(trimmed);
	while (len > 0 && (trimmed[len - 1] == ' ' || trimmed[len - 1] == '\t'))
		len--;
	if (len > 0 && trimmed[len - 1] == '|')
		return (1);
	return (0);
}
