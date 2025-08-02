/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:23:39 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/02 12:24:01 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_redir_out(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD)
		cmd->outfile = ft_strdup(tokens[*tkn_index].value);
}

void	handle_append_out(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD)
	{
		cmd->outfile = ft_strdup(tokens[*tkn_index].value);
		cmd->append = 1;
	}
}

void	handle_redir_in(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD)
		cmd->infile = ft_strdup(tokens[*tkn_index].value);
}

void	handle_heredoc(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD)
		cmd->heredoc_delim = ft_strdup(tokens[*tkn_index].value);
	else
		cmd->heredoc_delim = NULL;
}

void	handle_token(t_command *cmd, t_token *tokens, size_t *tkn_index,
		size_t *arg_index)
{
	if (tokens[*tkn_index].type == WORD)
		cmd->args[(*arg_index)++] = ft_strdup(tokens[*tkn_index].value);
	else if (tokens[*tkn_index].type == REDIR_OUT)
		handle_redir_out(cmd, tokens, tkn_index);
	else if (tokens[*tkn_index].type == APPEND_OUT)
		handle_append_out(cmd, tokens, tkn_index);
	else if (tokens[*tkn_index].type == REDIR_IN)
		handle_redir_in(cmd, tokens, tkn_index);
	else if (tokens[*tkn_index].type == HEREDOC)
		handle_heredoc(cmd, tokens, tkn_index);
}
