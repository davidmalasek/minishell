/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/24 17:46:26 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*parse(char *input)
{
	t_token		*tkns;
	t_command	*cmds;
	size_t		cmd_index;
	size_t		tkn_index;
	size_t		arg_index;

	tkns = tokenize(input);
	if (!tkns)
		return (NULL);
	cmds = malloc(sizeof(t_command) * (get_command_count(tkns) + 1));
	if (!cmds)
	{
		free(tkns);
		return (NULL);
	}
	cmd_index = 0;
	tkn_index = 0;
	arg_index = 0;
	while (cmd_index < get_command_count(tkns))
	{
		arg_index = 0;
		cmds[cmd_index].args = malloc(sizeof(char *) * (get_token_count(tkns)
					+ 1));
		cmds[cmd_index].infile = NULL;
		cmds[cmd_index].outfile = NULL;
		cmds[cmd_index].append = 0;
		cmds[cmd_index].pipe_to_next = 0;
		while (tkns[tkn_index].type != PIPE && tkns[tkn_index].type != -1)
		{
			if (tkns[tkn_index].type == WORD)
				cmds[cmd_index].args[arg_index++] = ft_strdup(tkns[tkn_index].value);
			tkn_index++;
		}
		cmds[cmd_index].pipe_to_next = NULL;
		if (tkns[tkn_index].type = PIPE)
		{
			cmds[cmd_index].pipe_to_next = 1;
			tkn_index++;
		}
		cmd_index++;
	}
	free(tkns);
	return (cmds);
}

/*
DAVID TODO:
- parsovani
- history
*/

/*
// ...existing code...
t_command	*parse(char *input)
{
	t_token		*tkns;
	size_t		cmd_count;
	size_t		i;
	t_command	*cmds;

	i = 0, j;
	cmd_count = 1;
	i = 0, j = 0, arg_idx;
	tkns = tokenize(input);
	if (!tkns)
		return (NULL);
	// 1. Count cmds (by PIPE)
	while (tkns[i].type != -1)
	{
		if (tkns[i].type == PIPE)
			cmd_count++;
		i++;
	}
	// 2. Allocate array of t_command
	cmds = malloc(sizeof(t_command) * (cmd_count + 1));
	if (!cmds)
		return (NULL);
	// 3. Fill cmds
	i = 0;
	j = 0;
	while (j < cmd_count)
	{
		// Initialize command
		cmds[j].args = malloc(sizeof(char *)
				* (get_array_length((char **)tkns) + 1));
		arg_idx = 0;
		cmds[j].infile = NULL;
		cmds[j].outfile = NULL;
		cmds[j].append = 0;
		cmds[j].pipe_to_next = 0;
		while (tkns[i].type != PIPE && tkns[i].type != -1)
		{
			if (tkns[i].type == WORD)
			{
				cmds[j].args[arg_idx++] = ft_strdup(tkns[i].value);
			}
			else if (tkns[i].type == REDIR_IN)
			{
				i++;
				if (tkns[i].type == WORD)
					cmds[j].infile = ft_strdup(tkns[i].value);
			}
			else if (tkns[i].type == REDIR_OUT)
			{
				i++;
				if (tkns[i].type == WORD)
				{
					cmds[j].outfile = ft_strdup(tkns[i].value);
					cmds[j].append = 0;
				}
			}
			else if (tkns[i].type == APPEND_OUT)
			{
				i++;
				if (tkns[i].type == WORD)
				{
					cmds[j].outfile = ft_strdup(tkns[i].value);
					cmds[j].append = 1;
				}
			}
			// HEREDOC handling can be added here
			i++;
		}
		cmds[j].args[arg_idx] = NULL;
		if (tkns[i].type == PIPE)
		{
			cmds[j].pipe_to_next = 1;
			i++;
		}
		j++;
	}
	// Mark end of array if needed (optional)
	// cmds[j].args = NULL;
	// Free tkns if needed
	free(tkns);
	return (cmds);
}
// ...existing code...
*/