/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 17:42:10 by tklaus            #+#    #+#             */
/*   Updated: 2025/08/14 17:42:22 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop(t_outfile_node *curr, int pipe_fd[2])
{
	char	*line;

	while (curr)
	{
		while (!g_signal_interrupted)
		{
			line = readline("> ");
			if (!line || strcmp(line, curr->filename) == 0)
				break ;
			if (curr->next == NULL)
				(write(pipe_fd[1], line, strlen(line)), write(pipe_fd[1], "\n",
						1));
			free(line);
		}
		if (g_signal_interrupted)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return (ERROR);
		}
		curr = curr->next;
	}
	if (line)
		free(line);
	return (SUCCESS);
}
