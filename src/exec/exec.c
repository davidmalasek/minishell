/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/04 11:57:23 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/**
 * Executes a command in a child process.
 * Handles redirections, pipes, builtins, and external commands.
 * If the command is not found, prints an error and exits with status 127.
 */

static void	exec_child_process(t_command *command, t_env *env, int *status,
		int pipes[4])
{
	char	**envp;
	char	*resolved_path;

	signal(SIGINT, sigint_handler_child);
	signal(SIGQUIT, SIG_DFL);
	redir_setup(command);
	pipe_setup(command, &pipes[2], &pipes[0]);
	envp = env_list_to_array(env);
	if (is_builtin(command->args[0]))
	{
		*status = exec_builtin(*command, env, *status);
		free_str_array(envp);
		exit(*status);
	}
	resolved_path = resolve_path(command->args[0], env);
	if (resolved_path)
	{
		execve(resolved_path, command->args, envp);
		free(resolved_path);
	}
	printf("minishell: command not found: %s\n", command->args[0]);
	free_str_array(envp);
	exit(127);
}

/**
 * Handles the parent process after forking a child.
 * Closes unused pipes and waits for the child process to finish.
 * Updates the shell status based on the child's exit status or signal.
 */

static void	exec_parent_process(t_command *command, int *status, int pipes[4])
{
	int	wstatus;

	if (pipes[0] > 0)
		close(pipes[0]);
	if (command->pipe_to_next)
	{
		close(pipes[3]);
		pipes[0] = pipes[2];
	}
	wstatus = 0;
	waitpid(-1, &wstatus, 0);
	if (WIFSIGNALED(wstatus))
		*status = 128 + WTERMSIG(wstatus);
	else if (WIFEXITED(wstatus))
		*status = WEXITSTATUS(wstatus);
}

/* pipes[0]=prev_pipe_read, pipes[1]=prev_pipe_write,
		pipes[2]=current_pipe_read, pipes[3]=current_pipe_write */

int	exec(t_command *command_list, t_env *env, int *status)
{
	pid_t	pid;
	int		pipes[4];

	setup_pipes(pipes);
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
	setup_signal_handlers();
	return (SUCCESS);
}
