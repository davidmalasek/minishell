/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:28:42 by tklaus            #+#    #+#             */
/*   Updated: 2025/08/09 17:44:26 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_file_list(t_outfile_node *list)
{
	t_outfile_node	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list->filename);
		free(list);
		list = tmp;
	}
}

void	cleanup_single_command(t_command *cmd)
{
	int	j;

	j = 0;
	if (cmd->args)
	{
		while (cmd->args[j])
		{
			free(cmd->args[j]);
			j++;
		}
		free(cmd->args);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cleanup_file_list(cmd->outfile_old);
	cleanup_file_list(cmd->infile_old);
	cleanup_file_list(cmd->heredoc_old);
}
