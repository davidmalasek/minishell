/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 09:53:15 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	alloc_command_args(t_command *cmd, t_token *tokens, size_t tkn_index)
{
	size_t	argc;

	argc = count_args(tokens, tkn_index);
	cmd->args = malloc(sizeof(char *) * (argc + 1));
	return (cmd->args != NULL);
}

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

t_command	*process_all_commands(t_command *cmds, t_token *tokens,
		int has_quotes)
{
	size_t	cmd_index;
	size_t	tkn_index;
	size_t	total_commands;
	int		ret;

	cmd_index = 0;
	tkn_index = 0;
	total_commands = get_command_count(tokens);
	while (cmd_index < total_commands)
	{
		cmds[cmd_index].has_quotes = has_quotes;
		ret = process_command(cmds, tokens, &cmd_index, &tkn_index);
		if (ret == 0)
			return (free_commands(cmds, cmd_index), cleanup_tokens(tokens),
				NULL);
		if (ret == -1)
			return (free_commands(cmds, cmd_index + 1), cleanup_tokens(tokens),
				NULL);
		handle_pipe(cmds, tokens, &cmd_index, &tkn_index);
	}
	return (cmds[cmd_index].args = NULL, cleanup_tokens(tokens), cmds);
}

t_command	*parse(char *input, t_env *env, int *last_exit_status)
{
	t_token		*tokens;
	t_command	*cmds;
	int			has_quotes;
	size_t		token_count;

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
	cmds = malloc(sizeof(t_command) * (get_command_count(tokens) + 1));
	if (!cmds)
		return (free(tokens), NULL);
	cmds = process_all_commands(cmds, tokens, has_quotes);
	if (!cmds)
		*last_exit_status = 2;
	return (cmds);
}
