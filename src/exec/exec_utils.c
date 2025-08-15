/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:16:59 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/15 11:12:03 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_pipes(int pipes[4])
{
	pipes[0] = -1;
	pipes[1] = -1;
	pipes[2] = -1;
	pipes[3] = -1;
}

void	child_setup(t_command *cmd, t_env *env, int pipes[4])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (redir_setup(cmd, env))
	{
		if (g_signal_interrupted)
			exit_shell(cmd, env, 130);
		exit_shell(cmd, env, EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_DFL);
	pipe_setup(cmd, &pipes[2], &pipes[0]);
}

/**
 * Checks if the given command is a builtin that must
 * be executed in the parent process.
 * Builtins: cd, exit, unset, export (with arguments).
 *
 * @return 1 if the command is a parent builtin, 0 otherwise.
 */
int	is_parent_builtin(t_command *command)
{
	if (!command || !command->args || !command->args[0])
		return (0);
	if (ft_strcmp(command->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(command->args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(command->args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(command->args[0], "export") == 0)
	{
		if (command->args[1] == NULL)
			return (0);
		return (1);
	}
	return (0);
}

/**
 * Executes a builtin command and returns its exit status.
 * Supports: cd, echo, pwd, export, unset, env, exit.
 *
 * @return The exit status of the builtin command, or ERROR on failure.
 */

int	exec_builtin(t_command command, t_env *env, int status,
		t_exec_context exec_context)
{
	if (!command.args || !command.args[0])
		return (ERROR);
	if (ft_strcmp(command.args[0], "cd") == 0)
		return (ft_cd(command.args, env));
	else if (ft_strcmp(command.args[0], "echo") == 0)
		return (ft_echo(command.args));
	else if (ft_strcmp(command.args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(command.args[0], "export") == 0)
		return (ft_export(command.args, env));
	else if (ft_strcmp(command.args[0], "unset") == 0)
		return (ft_unset(command.args, env));
	else if (ft_strcmp(command.args[0], "env") == 0)
		return (ft_env(command.args, env));
	else if (ft_strcmp(command.args[0], "exit") == 0)
		return (ft_exit(command.args, status, exec_context));
	return (ERROR);
}
