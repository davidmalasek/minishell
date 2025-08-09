/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:25:07 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/09 17:46:54 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Initializes all fields of a t_command struct to default values.
 */
void	init_command(t_command *command)
{
	command->args = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->append = 0;
	command->pipe_to_next = 0;
	command->heredoc_delim = NULL;
}

/**
 * Counts the number of argument tokens (WORD) for a command,
 * stopping at a pipe or end.
 */
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

/**
 * Frees all memory allocated for an array of commands.
 */
void	free_commands(t_command *commands, size_t count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < count)
	{
		if (commands[i].args)
		{
			j = 0;
			while (commands[i].args[j])
			{
				free(commands[i].args[j]);
				j++;
			}
			free(commands[i].args);
		}
		free(commands[i].infile);
		free(commands[i].outfile);
		free(commands[i].heredoc_delim);
		i++;
	}
	free(commands);
}

/**
 * Fills a command struct with its arguments and redirections.
 */
int	fill_command_fields(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	size_t	arg_index;
	int		result;

	arg_index = 0;
	while (tokens[*tkn_index].type != PIPE && tokens[*tkn_index].type != -1)
	{
		result = handle_token(cmd, tokens, tkn_index, &arg_index);
		if (result == ERROR)
		{
			cmd->args[arg_index] = NULL;
			return (ERROR);
		}
		(*tkn_index)++;
	}
	cmd->args[arg_index] = NULL;
	return (SUCCESS);
}

/**
 * Frees the old value of a string pointer
 * and sets it to a new duplicated value.
 */
void	free_and_set(char **target, char *new_value)
{
	if (*target)
		free(*target);
	*target = ft_strdup(new_value);
}
