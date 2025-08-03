/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/03 11:24:31 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	exec_builtin(t_command command, t_env *env, int status)
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
		return (ft_exit(command.args, status));
	return (ERROR);
}

static void	exec_child_process(t_command *command, t_env *env, int *status,
		int pipes[4])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pipe_setup(command, &pipes[2], &pipes[0]);
	redir_setup(command);
	if (is_builtin(command->args[0]))
		*status = exec_builtin(*command, env, *status);
	else if (execve(resolve_path(command->args[0], env), command->args,
			env_list_to_array(env)) == -1)
	{
		printf("minishell: command not found: %s\n", command->args[0]);
		exit(EXIT_FAILURE);
	}
	exit(*status);
}

static void	exec_parent_process(t_command *command, int *status, int pipes[4])
{
	int	wait_status;

	if (pipes[0] > 0)
		close(pipes[0]);
	if (command->pipe_to_next)
	{
		close(pipes[3]);
		pipes[0] = pipes[2];
	}
	waitpid(-1, &wait_status, 0);
	if (WIFSIGNALED(wait_status) && WTERMSIG(wait_status) == SIGINT)
	{
		*status = 130;
		write(STDOUT_FILENO, "\n", 1);
	}
	else if (WIFEXITED(wait_status))
		*status = WEXITSTATUS(wait_status);
}
/* pipes[0]=prev_pipe_read, pipes[1]=prev_pipe_write,
		pipes[2]=current_pipe_read, pipes[3]=current_pipe_write */

int	exec(t_command *command_list, t_env *env, int *status)
{
	pid_t	pid;
	int		pipes[4];

	pipes[0] = -1;
	pipes[1] = -1;
	pipes[2] = -1;
	pipes[3] = -1;
	while (command_list->args != NULL)
	{
		if (is_parent_builtin(command_list))
		{
			*status = exec_builtin(*command_list, env, *status);
			command_list++;
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		if (command_list->pipe_to_next)
			pipe(&pipes[2]);
		pid = fork();
		if (pid == 0)
			exec_child_process(command_list, env, status, pipes);
		else
			exec_parent_process(command_list, status, pipes);
		command_list++;
	}
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_DFL);
	return (SUCCESS);
}
