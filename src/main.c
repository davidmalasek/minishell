/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 23:54:07 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
TODO
cleanup - exit sequence
norminette
memory leak check
heredoc
variable expansions

DAVID
- single quotes
- heredoc stale nefunguje
*/

// Define the global variable for signal interruption
int g_signal_interrupted = 0;

t_env *initialize_shell(char **envp)
{
	t_env *env;

	env = load_env(envp);	 // Copy env vars if needed
	setup_signal_handlers(); // Ctrl-C, Ctrl-\, Ctrl-D
	return (env);
}

void print_command(t_command *command_list)
{
	int i;
	t_command *cmd = command_list;

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

		printf("heredoc_delimiter: ");
		if (cmd->heredoc_delimiter)
			printf("'%s'\n", cmd->heredoc_delimiter);
		else
			printf("(none)\n");

		printf("append: %d\n", cmd->append);
		printf("pipe_to_next: %d\n", cmd->pipe_to_next);
		printf("-----------------\n");
		cmd++;
	}
}

int main_loop(t_env *env)
{

	int status;
	char *input;
	t_command *command_list;

	status = 0;
	while (1)
	{
		if (status == ECHON)
		{
			ft_putchar_fd('\n', 1);
			status = 0;
		}

		// Reset the signal flag before calling readline
		g_signal_interrupted = 0;

		input = readline("minishell ➜ ");

		// Check if readline returned NULL. This can happen for Ctrl+D (EOF) or Ctrl+C.
		if (input == NULL)
		{
			if (g_signal_interrupted) // This was Ctrl+C
				continue;

			else // This was Ctrl+D (EOF). Exit the shell.
			{
				write(STDOUT_FILENO, "exit\n", 5);
				exit(EXIT_SUCCESS);
			}
		}

		// If input is an empty string (e.g., user just pressed Enter)
		if (input[0] == '\0')
		{
			free(input); // Free the memory allocated by readline for the empty string
			continue;
		}

		// Add non-empty input to history
		if (input && *input)
			add_history(input);

		// TODO TOMÁŠ: tady potřebuju abys mi předal ten last_exit_status
		command_list = parse(input, env, status);
		//print_command(command_list);
		// Parse input into structured commands
		exec(command_list, env, &status);
		// cleanup(command_list);
		free(input); // Free input after parsing/execution
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env *env;

	(void)argc;
	(void)argv;
	env = initialize_shell(envp);
	main_loop(env);
}
