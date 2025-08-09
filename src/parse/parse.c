/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/09 17:47:20 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Allocates memory for the args array in a command.
 */
int	alloc_command_args(t_command *cmd, t_token *tokens, size_t tkn_index)
{
	size_t	argc;

	argc = count_args(tokens, tkn_index);
	cmd->args = malloc(sizeof(char *) * (argc + 1));
	if (cmd->args)
		cmd->args[argc] = NULL;
	return (cmd->args != NULL);
}

/**
 * Fills a single t_command struct with all its arguments and redirections.
 */
int	process_command(t_command *cmds, t_token *tokens, size_t *cmd_index,
		size_t *tkn_index)
{
	init_command(&cmds[*cmd_index]);
	if (!alloc_command_args(&cmds[*cmd_index], tokens, *tkn_index))
		return (0);
	if (fill_command_fields(&cmds[*cmd_index], tokens, tkn_index) == ERROR)
		return (-1);
	if (cmds[*cmd_index].args[0] == NULL)
		return (-1);
	(*cmd_index)++;
	return (1);
}

/**
 * Handles the pipe operator between commands.
 */
void	handle_pipe(t_command *cmds, t_token *tokens, size_t *cmd_index,
		size_t *tkn_index)
{
	if (tokens[*tkn_index].type == PIPE)
	{
		if (*cmd_index > 0)
			cmds[*cmd_index - 1].pipe_to_next = 1;
		(*tkn_index)++;
	}
}

/**
 * Processes all commands in the token list, filling the cmds array.
 */
t_command	*process_all_commands(t_command *cmds, t_token *tokens,
		int has_quotes)
{
	size_t	cmd_index;
	size_t	tkn_index;
	size_t	total_commands;
	int		ret;
	size_t	start_idx;

	cmd_index = 0;
	tkn_index = 0;
	total_commands = get_command_count(tokens);
	while (cmd_index < total_commands)
	{
		start_idx = cmd_index;
		ret = process_command(cmds, tokens, &cmd_index, &tkn_index);
		if (ret == 0)
			return (free_commands(cmds, cmd_index), cleanup_tokens(tokens),
				NULL);
		if (ret == -1)
			return (free_commands(cmds, cmd_index + 1), cleanup_tokens(tokens),
				NULL);
		handle_pipe(cmds, tokens, &cmd_index, &tkn_index);
		cmds[start_idx].has_quotes = has_quotes;
	}
	return (cmds[cmd_index].args = NULL, cleanup_tokens(tokens), cmds);
}

/**
 * Main entry point for parsing user input into commands.
 */
t_command	*parse(char *input, t_env *env, int *last_exit_status)
{
	t_token		*tokens;
	t_command	*cmds;
	int			has_quotes;
	size_t		token_count;
	size_t		ncmds;

	tokens = tokenize(input, env, *last_exit_status, &has_quotes);
	if (!tokens)
		return (NULL);
	token_count = get_token_count(tokens);
	if (token_count > 0 && tokens[token_count - 1].type == PIPE)
	{
		printf("minishell: syntax error: unexpected end of file\n");
		cleanup_tokens(tokens);
		*last_exit_status = 2;
		return (NULL);
	}
	ncmds = get_command_count(tokens) + 1;
	cmds = ft_calloc(ncmds, sizeof(t_command));
	if (!cmds)
		return (free(tokens), NULL);
	cmds = process_all_commands(cmds, tokens, has_quotes);
	if (!cmds)
		*last_exit_status = 2;
	return (cmds);
}
