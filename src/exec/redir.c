/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:22:53 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/07 10:15:23 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int pipe_setup(t_command *command, int pipe_fd[2], int prev_pipe[2])
{
    if (prev_pipe[0])
    {
        dup2(prev_pipe[0], STDIN_FILENO);
        close(prev_pipe[0]);
    }
    if (command->pipe_to_next)
    {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]); // Only close read end if piping to next command
    }
    return SUCCESS;
}

int temp_file(char *delimiter)
{
    (void)delimiter;
    return 1;
}

int heredoc_setup(t_command *command)
{
    int heredoc_fd = 0;
    heredoc_fd = temp_file(command->heredoc_delimiter);
    dup2(heredoc_fd, STDIN_FILENO);
    close(heredoc_fd);
    return heredoc_fd;
}

int redir_setup(t_command *command)
{
    int fd = 0;
    // --- INPUT REDIRECTION ---
    if (command->infile)
    {
        fd = open(command->infile, O_RDONLY);
        if (fd == -1)
        {
            perror("minishell");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    // --- HEREDOC ---
    if (command->heredoc_delimiter)
        heredoc_setup(command);

    // --- OUTPUT REDIRECTION ---
    if (command->outfile)
    {
        if (command->append)
            fd = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    return SUCCESS;
}
