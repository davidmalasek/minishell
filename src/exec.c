/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/06/22 12:39:53 by tomasklaus       ###   ########.fr       */
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
int fork_and_exec (char **command){
    pid_t child_pid;
	int stat_loc;

	child_pid = fork();
	if (child_pid == 0)
	{
		execvp(command[0], command);
	}
	else
	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
	}
}

void exec(char **command_table)
{
	
}

