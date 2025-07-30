/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:22:53 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/30 22:55:24 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_setup(t_command *command, int pipe_fd[2], int prev_pipe[2])
{
	if (prev_pipe[0] > 0)
	{
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
	}
	if (command->pipe_to_next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	return (SUCCESS);
}

static int	input_redir(const char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	output_redir(const char *outfile, int append)
{
	int	fd;

	if (append)
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	heredoc_redir(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	pipe(pipe_fd);
	printf("setting up heredoc");
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
			break ;
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	return (SUCCESS);
}

int	redir_setup(t_command *command)
{
	if (command->infile)
		input_redir(command->infile);
	if (command->heredoc_delimiter)
		heredoc_redir(command->heredoc_delimiter);
	if (command->outfile)
		output_redir(command->outfile, command->append);
	return (SUCCESS);
}
