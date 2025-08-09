/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:22:53 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/09 17:46:38 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Sets up the pipe file descriptors for the current command.
 * If there is a previous pipe, duplicates its read end to STDIN and closes it.
 * If the current command pipes to the next,
 * duplicates the write end of the current pipe to STDOUT,
 */
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

/**
 * Redirects STDIN to read from the specified input file.
 */
int	input_redir(const char *infile, t_command *command)
{
	int				fd;
	t_outfile_node	*curr;

	curr = command->infile_old;
	while (curr)
	{
		if (curr->filename && access(curr->filename, F_OK) != 0)
		{
			fprintf(stderr, "minishell: %s: No such file or directory\n",
				curr->filename);
			exit(EXIT_FAILURE);
		}
		curr = curr->next;
	}
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

/**
 * Redirects STDOUT to write to the specified output file.
 * Opens the file in write mode (append or truncate based on the 'append' flag),
 */
int	output_redir(const char *outfile, int append)
{
	int	fd;

	if (append)
	{
		fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
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

/**
 * Heredoc redirection by reading lines from the
 * user until the delimiter is encountered.
 * Each line is written to a pipe, which is then duplicated to STDIN.
 */

int	heredoc_redir(t_command *command)
{
	int				pipe_fd[2];
	t_outfile_node	*curr;
	char			*line;

	pipe(pipe_fd);
	curr = command->heredoc_old;
	while (curr)
	{
		while (1)
		{
			line = readline("> ");
			if (!line || strcmp(line, curr->filename) == 0)
				break ;
			if (curr->next == NULL)
				(write(pipe_fd[1], line, strlen(line)), write(pipe_fd[1], "\n",
						1));
			free(line);
		}
		curr = curr->next;
	}
	if (line)
		free(line);
	return (close(pipe_fd[1]), dup2(pipe_fd[0], STDIN_FILENO),
		close(pipe_fd[0]), SUCCESS);
}

int	redir_setup(t_command *command)
{
	t_outfile_node	*curr;
	int				fd;

	if (command->infile)
		input_redir(command->infile, command);
	if (command->heredoc_delim)
		heredoc_redir(command);
	curr = command->outfile_old;
	while (curr)
	{
		fd = open(curr->filename, O_WRONLY | O_CREAT, 0644);
		if (fd == -1)
		{
			perror("minishell: could not open file");
			exit(EXIT_FAILURE);
		}
		else
			close(fd);
		curr = curr->next;
	}
	if (command->outfile)
		output_redir(command->outfile, command->append);
	return (SUCCESS);
}
