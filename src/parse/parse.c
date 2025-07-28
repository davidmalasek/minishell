/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 12:35:37 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_command(t_command *command)
{
	command->infile = NULL;
	command->outfile = NULL;
	command->append = 0;
	command->pipe_to_next = 0;
	command->heredoc_delimiter = NULL;
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

void	fill_command_fields(t_command *commands, t_token *tokens,
		size_t *tkn_index)
{
	size_t	arg_index;

	arg_index = 0;
	while (tokens[*tkn_index].type != PIPE && tokens[*tkn_index].type != -1)
	{
		if (tokens[*tkn_index].type == WORD)
			commands->args[arg_index++] = ft_strdup(tokens[*tkn_index].value);
		else if (tokens[*tkn_index].type == REDIR_OUT)
		{
			(*tkn_index)++;
			if (tokens[*tkn_index].type == WORD)
				commands->outfile = ft_strdup(tokens[*tkn_index].value);
		}
		else if (tokens[*tkn_index].type == APPEND_OUT)
		{
			(*tkn_index)++;
			if (tokens[*tkn_index].type == WORD)
			{
				commands->outfile = ft_strdup(tokens[*tkn_index].value);
				commands->append = 1;
			}
		}
		else if (tokens[*tkn_index].type == REDIR_IN)
		{
			(*tkn_index)++;
			if (tokens[*tkn_index].type == WORD)
				commands->infile = ft_strdup(tokens[*tkn_index].value);
		}
		else if (tokens[*tkn_index].type == HEREDOC)
		{
			(*tkn_index)++;
			if (tokens[*tkn_index].type == WORD)
				commands->heredoc_delimiter = ft_strdup(tokens[*tkn_index].value);
			else
				commands->heredoc_delimiter = NULL;
		}
		(*tkn_index)++;
	}
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
		free(commands[i].heredoc_delimiter);
		i++;
	}
	free(commands);
}

t_command	*parse(char *input, t_env *env, int last_exit_status)
{
	t_token		*tokens;
	t_command	*commands;
	size_t		cmd_index;
	size_t		tkn_index;
	int			has_quotes;

	tokens = tokenize(input, env, last_exit_status, &has_quotes);
	if (!tokens)
		return (NULL);
	commands = malloc(sizeof(t_command) * (get_command_count(tokens) + 1));
	if (!commands)
		return (free(tokens), NULL);
	cmd_index = 0;
	tkn_index = 0;
	while (cmd_index < get_command_count(tokens))
	{
		init_command(&commands[cmd_index]);
		commands[cmd_index].args = malloc(sizeof(char *) * (count_args(tokens,
						tkn_index) + 1));
		if (!commands[cmd_index].args)
			return (free_commands(commands, cmd_index), free(tokens), NULL);
		fill_command_fields(&commands[cmd_index], tokens, &tkn_index);
		commands[cmd_index].has_quotes = has_quotes;
		if (tokens[tkn_index].type == PIPE)
		{
			commands[cmd_index].pipe_to_next = 1;
			tkn_index++;
		}
		cmd_index++;
	}
	commands[cmd_index].args = NULL;
	return (free(tokens), commands);
}
