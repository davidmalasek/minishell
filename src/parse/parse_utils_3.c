/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 09:17:12 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/09 09:59:26 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_output_old(t_command *cmd, char *value)
{
	t_outfile_node	*new_node;
	t_outfile_node	*curr;

	if (!value)
		return (SUCCESS);
	new_node = malloc(sizeof(t_outfile_node));
	if (!new_node)
		return (ERROR);
	new_node->filename = ft_strdup(value);
	if (!new_node->filename)
		return (free(new_node), ERROR);
	new_node->next = NULL;
	if (!cmd->outfile_old)
		cmd->outfile_old = new_node;
	else
	{
		curr = cmd->outfile_old;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
	return (SUCCESS);
}

void	all_infiles(t_command *cmd, char *value)
{
	t_outfile_node	*new_node;
	t_outfile_node	*curr;

	new_node = malloc(sizeof(t_outfile_node));
	if (!new_node)
		return ;
	if (!value)
		return ;
	new_node->filename = ft_strdup(value);
	if (!new_node->filename)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (!cmd->infile_old)
		cmd->infile_old = new_node;
	else
	{
		curr = cmd->infile_old;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}

void	all_heredocs(t_command *cmd, char *value)
{
	t_outfile_node	*new_node;
	t_outfile_node	*curr;

	new_node = malloc(sizeof(t_outfile_node));
	if (!new_node)
		return ;
	if (!value)
		return ;
	new_node->filename = ft_strdup(value);
	if (!new_node->filename)
	{
		free(new_node);
		return ;
	}
	new_node->next = NULL;
	if (!cmd->heredoc_old)
		cmd->heredoc_old = new_node;
	else
	{
		curr = cmd->heredoc_old;
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
	}
}
