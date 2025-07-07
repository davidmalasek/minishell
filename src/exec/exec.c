/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/07 10:17:55 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
TODO:
co delat kdyz uzivatel zada option u funkce kde nemusi byt - mozna osetrit uz v parsing?
co delat kdyz uzivatel zada vic nebo min argumentu nez je potreba
co se stane kdyz se zada neexistujici command?

Redirection handling in command table
Pipe setup with fork + dup2
Heredoc (most annoying, do it last)
$? support — just track WEXITSTATUS after commands

 */

int is_builtin(char *str)
{
    if (!str)
        return (0);
    char *builtins[] = {
        "echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int i;

    i = 0;
    while (builtins[i])
    {
        if (ft_strcmp(str, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

int is_parent_builtin(char *str)
{
    if (!str)
        return (0);
    char *parent_builtins[] = {"cd", "exit", "export", "unset", NULL};
    int i;

    i = 0;
    while (parent_builtins[i])
    {
        if (ft_strcmp(str, parent_builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

int exec_builtin(t_command command, t_env *env)
{
    if (!command.args || !command.args[0])
        return (ERROR);

    if (ft_strcmp(command.args[0], "cd") == 0)
        return ft_cd(command.args, env);
    else if (ft_strcmp(command.args[0], "echo") == 0)
        return ft_echo(command.args);
    else if (ft_strcmp(command.args[0], "pwd") == 0)
        return ft_pwd();
    else if (ft_strcmp(command.args[0], "export") == 0)
        return ft_export(command.args, env);
    else if (ft_strcmp(command.args[0], "unset") == 0)
        return ft_unset(command.args, env);
    else if (ft_strcmp(command.args[0], "env") == 0)
        return ft_env(command.args, env);
    else if (ft_strcmp(command.args[0], "exit") == 0)
        return ft_exit(command.args, 0); // pass status

    return (SUCCESS);
}

int exec(t_command *command_list, t_env *env)
{
    pid_t pid;
    int status;
    int prev_pipe[2];

    while (command_list->args != NULL)
    {
        if (is_parent_builtin(command_list->args[0]) && !command_list->pipe_to_next)
        {
            exec_builtin(*command_list, env);
            command_list++;
            continue;
        }
        int pipe_fd[2];
        if (command_list->pipe_to_next)
            pipe(pipe_fd);
        pid = fork();
        if (pid == 0)
        {
            pipe_setup(command_list, pipe_fd, prev_pipe);
            redir_setup(command_list);
            if (is_builtin(command_list->args[0]))
                status = exec_builtin(*command_list, env);
            else if (execve(resolve_path(command_list->args[0]), command_list->args, env_list_to_array(env)) == -1)
            {
                // perror("minishell");
                printf("minishell: command not found: %s\n", command_list->args[0]);
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        else
        {
            if (prev_pipe[0])
                close(prev_pipe[0]);
            if (command_list->pipe_to_next)
            {
                close(pipe_fd[1]);         // write end
                prev_pipe[0] = pipe_fd[0]; // save read end
            }
            waitpid(pid, &status, WUNTRACED);
        }
        command_list++;
    }
    return SUCCESS;
}
