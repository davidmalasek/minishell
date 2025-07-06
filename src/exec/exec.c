/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 11:45:28 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
TODO:
co delat kdyz uzivatel zada option u funkce kde nemusi byt - mozna osetrit uz v parsing?
co delat kdyz uzivatel zada vic nebo min argumentu nez je potreba
co se stane kdyz se zada neexistujici command?

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

int fork_and_exec(t_command command, t_env *env)
{
    pid_t child_pid;
    int stat_loc;

    child_pid = fork();
    if (child_pid == 0)
    {
        execve(command.args[0], command.args, env_list_to_array(env));
    }
    else
    {
        waitpid(child_pid, &stat_loc, WUNTRACED);
    }
    return SUCCESS;
}

int exec_builtin(t_command command, t_env *env)
{
    if (!command.args || !command.args[0])
        return (0);

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

    return (0);
}

int exec(t_command *command_list, t_env *env)
{

    while (command_list->args != NULL)
    {
        if (is_builtin(command_list->args[0]))
            exec_builtin(*command_list, env);
        else
            fork_and_exec(*command_list, env);

        command_list++;
    }
    return SUCCESS;
}
