/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:25:07 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/02 12:26:16 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_command(t_command *command)
{
	command->infile = NULL;
	command->outfile = NULL;
	command->append = 0;
	command->pipe_to_next = 0;
	command->heredoc_delim = NULL;
}

size_t	count_args(t_token *tokens, size_t index)
{
	size_t	count;

	count = 0;
	while (tokens[index].type != PIPE && tokens[index].type != -1)
	{
		if (tokens[index].type == WORD)
			count++;
		index++;
	}
	return (count);
}

void	free_commands(t_command *commands, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(commands[i].args);
		free(commands[i].infile);
		free(commands[i].outfile);
		free(commands[i].heredoc_delim);
		i++;
	}
	free(commands);
}

void	fill_command_fields(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	size_t	arg_index;

	arg_index = 0;
	while (tokens[*tkn_index].type != PIPE && tokens[*tkn_index].type != -1)
	{
		handle_token(cmd, tokens, tkn_index, &arg_index);
		(*tkn_index)++;
	}
	cmd->args[arg_index] = NULL;
}
