/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 11:56:25 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			g_signal_interrupted = 0;

/*
HOW TO USE:
- add print_command(command_list) to execute_and_cleanup function
void	print_command(t_command *command_list)
{
	int			i;
	t_command	*cmd;

	cmd = command_list;
	while (cmd && cmd->args)
	{
		printf("---- Command ----\n");
		printf("args: ");
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("'%s' ", cmd->args[i]);
				i++;
			}
		}
		else
		{
			printf("(none)");
		}
		printf("\n");
		printf("infile: ");
		if (cmd->infile)
			printf("'%s'\n", cmd->infile);
		else
			printf("(none)\n");
		printf("outfile: ");
		if (cmd->outfile)
			printf("'%s'\n", cmd->outfile);
		else
			printf("(none)\n");
		printf("heredoc_delim: ");
		if (cmd->heredoc_delim)
			printf("'%s'\n", cmd->heredoc_delim);
		else
			printf("(none)\n");
		printf("append: %d\n", cmd->append);
		printf("pipe_to_next: %d\n", cmd->pipe_to_next);
		printf("-----------------\n");
		cmd++;
	}
}
*/

static void	execute_and_cleanup(char *input, t_env *env, int *status)
{
	t_command	*command_list;

	command_list = parse(input, env, status);
	if (!command_list)
	{
		free(input);
		return ;
	}
	exec(command_list, env, status);
	cleanup_commands(command_list);
	free(input);
}
/**
 * Calls get_input() to read a line of input from the user.
 * Checks if the input is empty or if a signal (such as Ctrl+C) was received
 * using handle_empty_or_signal(). If so,updates status and continues to the
 * next iteration without executing a command.
 * Checks for invalid input (such as syntax errors)
 * using handle_invalid_input().
 * If invalid, updates status and continues to the next iteration.
 * Executes the command and performs necessary
 * cleanup using execute_and_cleanup(),
 * passing the input, environment, and status pointer.
 */

int	main_loop(t_env *env)
{
	int		status;
	char	*input;

	status = 0;
	while (1)
	{
		input = get_input();
		if (handle_empty_or_signal(input, &status))
			continue ;
		if (handle_invalid_input(input, &status))
			continue ;
		g_signal_interrupted = 0;
		execute_and_cleanup(input, env, &status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = initialize_shell(envp);
	main_loop(env);
	cleanup_env(env);
	return (0);
}
