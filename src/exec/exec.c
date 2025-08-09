/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:27:04 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/09 17:52:00 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Executes a command in a child process.
 * Handles redirections, pipes, builtins, and external commands.
 * If the command is not found, prints an error and exits with status 127.
 */

static void	exec_child_process(t_command *cmd, t_exec_context exec_context,
		int *status, int pipes[4])
{
	char	**envp;
	char	*path;
	t_env	*env;

	env = exec_context.env;
	envp = child_setup(cmd, env, pipes);
	if (is_builtin(cmd->args[0]))
	{
		if (is_parent_builtin(cmd))
			exit(0);
		*status = exec_builtin(*cmd, env, *status, exec_context);
		free_str_array(envp);
		exit(*status);
	}
	path = resolve_path(cmd->args[0], env);
	if (path)
	{
		execve(path, cmd->args, envp);
		free(path);
	}
	if (cmd->outfile || cmd->pipe_to_next)
		dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("minishell: command not found: %s\n", cmd->args[0]);
	free_str_array(envp);
	exit(127);
}

/**
 * Handles the parent process after forking a child.
 * Closes unused pipes and waits for the child process to finish.
 * Updates the shell status based on the child's exit status or signal.
 */

static void	exec_parent_process(t_command *command, int pipes[4])
{
	if (pipes[0] > 0)
		close(pipes[0]);
	if (command->pipe_to_next)
	{
		close(pipes[3]);
		pipes[0] = pipes[2];
	}
	else
	{
		pipes[0] = -1;
	}
}

/* pipes[0]=prev_pipe_read, pipes[1]=prev_pipe_write,
		pipes[2]=current_pipe_read, pipes[3]=current_pipe_write */

static void	exec_command_loop(t_exec_context exec_context, int *status,
		int pipes[4], pid_t *last_pid)
{
	pid_t		pid;
	t_command	*cmd;

	cmd = exec_context.command_list;
	while (cmd->args != NULL)
	{
		if (is_parent_builtin(cmd) && pipes[0] < 0 && !cmd->pipe_to_next)
		{
			*status = exec_builtin(*cmd, exec_context.env, *status,
					exec_context);
			cmd++;
			continue ;
		}
		if (cmd->pipe_to_next)
			pipe(&pipes[2]);
		pid = fork();
		if (pid == 0)
			exec_child_process(cmd, exec_context, status, pipes);
		else
		{
			*last_pid = pid;
			exec_parent_process(cmd, pipes);
		}
		cmd++;
	}
}

static void	wait_for_children(pid_t last_pid, int *status)
{
	int		wstatus;
	pid_t	wpid;

	wpid = wait(&wstatus);
	while (wpid > 0)
	{
		if (wpid == last_pid)
		{
			if (WIFSIGNALED(wstatus))
			{
				*status = 128 + WTERMSIG(wstatus);
				if (WTERMSIG(wstatus) == SIGINT)
					write(STDOUT_FILENO, "\n", 1);
			}
			else if (WIFEXITED(wstatus))
				*status = WEXITSTATUS(wstatus);
		}
		wpid = wait(&wstatus);
	}
}

int	exec(t_command *command_list, t_env *env, int *status)
{
	int				pipes[4];
	pid_t			last_pid;
	t_exec_context	exec_context;

	exec_context.command_list = command_list;
	exec_context.env = env;
	last_pid = -1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	setup_pipes(pipes);
	exec_command_loop(exec_context, status, pipes, &last_pid);
	if (pipes[0] > 0)
		close(pipes[0]);
	wait_for_children(last_pid, status);
	setup_signal_handlers();
	return (SUCCESS);
}
