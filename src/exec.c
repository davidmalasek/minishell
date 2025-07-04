/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/06/22 13:40:54 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* executor(command_table) {
    for each command in command_table {
        if (is_builtin(command))
            exec_builtin(command);
        else
            fork_and_exec(command);  // handle I/O redirections and pipes
    }
}

exec_builtin(cmd) {
    if (cmd.name == "cd")
        builtin_cd(cmd.args);
    else if (cmd.name == "echo")
        builtin_echo(cmd.args);
    ...
} */

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

int fork_and_exec(t_command command)
{
    pid_t child_pid;
    int stat_loc;

    child_pid = fork();
    if (child_pid == 0)
    {
        execvp(command.args[0], command.args);
    }
    else
    {
        waitpid(child_pid, &stat_loc, WUNTRACED);
    }
}

int exec_builtin(t_command command)
{
}

void exec(t_command *command)
{
    int i;
    i = 0;

    while (command)
    {
        if (is_builtin(command->args[0]))
            exec_builtin(*command);
        else
            fork_and_exec(*command);

        command++;
    }
}
