/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:23:39 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/09 09:51:56 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Handles the > redirection.
 */
int	handle_redir_out(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD && tokens[*tkn_index].value)
	{
		if (check_output_old(cmd, cmd->outfile))
			return (ERROR);
		free_and_set(&cmd->outfile, tokens[*tkn_index].value);
		cmd->append = 0;
		return (SUCCESS);
	}
	else if (tokens[*tkn_index].type == -1)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (ERROR);
	}
	else
	{
		if (tokens[*tkn_index].value)
			printf("minishell: syntax error near unexpected token '%s'\n",
				tokens[*tkn_index].value);
		else
			printf("minishell: syntax error near unexpected token '>'\n");
		return (ERROR);
	}
}

/**
 * Handles the >> redirection.
 */
int	handle_append_out(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD && tokens[*tkn_index].value)
	{
		if (check_output_old(cmd, cmd->outfile))
			return (ERROR);
		free_and_set(&cmd->outfile, tokens[*tkn_index].value);
		cmd->append = 1;
		return (SUCCESS);
	}
	else if (tokens[*tkn_index].type == -1)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (ERROR);
	}
	else
	{
		if (tokens[*tkn_index].value)
			printf("minishell: syntax error near unexpected token '%s'\n",
				tokens[*tkn_index].value);
		else
			printf("minishell: syntax error near unexpected token '>>'\n");
		return (ERROR);
	}
}

/**
 * Handles the < redirection.
 */
int	handle_redir_in(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD && tokens[*tkn_index].value)
	{
		all_infiles(cmd, tokens[*tkn_index].value);
		free_and_set(&cmd->infile, tokens[*tkn_index].value);
		return (SUCCESS);
	}
	else if (tokens[*tkn_index].type == -1)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (ERROR);
	}
	else
	{
		if (tokens[*tkn_index].value)
			printf("minishell: syntax error near unexpected token '%s'\n",
				tokens[*tkn_index].value);
		else
			printf("minishell: syntax error near unexpected token '<'\n");
		return (ERROR);
	}
}

/**
 * Handles the << heredoc redirection.
 */
int	handle_heredoc(t_command *cmd, t_token *tokens, size_t *tkn_index)
{
	(*tkn_index)++;
	if (tokens[*tkn_index].type == WORD && tokens[*tkn_index].value)
	{
		all_heredocs(cmd, tokens[*tkn_index].value);
		free_and_set(&cmd->heredoc_delim, tokens[*tkn_index].value);
		return (SUCCESS);
	}
	else if (tokens[*tkn_index].type == -1)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		cmd->heredoc_delim = NULL;
		return (ERROR);
	}
	else
	{
		if (tokens[*tkn_index].value)
			printf("minishell: syntax error near unexpected token '%s'\n",
				tokens[*tkn_index].value);
		else
			printf("minishell: syntax error near unexpected token '<<'\n");
		cmd->heredoc_delim = NULL;
		return (ERROR);
	}
}

/**
 * Processes a single token for a command.
 */
int	handle_token(t_command *cmd, t_token *tokens, size_t *tkn_index,
		size_t *arg_index)
{
	if (tokens[*tkn_index].type == WORD)
	{
		cmd->args[(*arg_index)++] = ft_strdup(tokens[*tkn_index].value);
		return (SUCCESS);
	}
	else if (tokens[*tkn_index].type == REDIR_OUT)
		return (handle_redir_out(cmd, tokens, tkn_index));
	else if (tokens[*tkn_index].type == APPEND_OUT)
		return (handle_append_out(cmd, tokens, tkn_index));
	else if (tokens[*tkn_index].type == REDIR_IN)
		return (handle_redir_in(cmd, tokens, tkn_index));
	else if (tokens[*tkn_index].type == HEREDOC)
		return (handle_heredoc(cmd, tokens, tkn_index));
	return (SUCCESS);
}
