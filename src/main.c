/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 22:17:52 by tomasklaus       ###   ########.fr       */
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

DAVID - single quotes
*/

t_env *initialize_shell(char **envp)
{
	t_env *env;

	env = load_env(envp); // Copy env vars if needed
	// setup_signal_handlers(); // Ctrl-C, Ctrl-\, Ctrl-D
	// init_history();				// Optional: readline history
	return (env);
	env = load_env(envp);	 // Copy env vars if needed
	setup_signal_handlers(); // Ctrl-C, Ctrl-\, Ctrl-D
	return (env);
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
		input = readline("minishell ➜ ");
		if (input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		if (input && *input)
			add_history(input);
		// TODO TOMÁŠ: tady potřebuju abys mi předal ten last_exit_status
		command_list = parse(input, env, status);
		// Parse input into structured commands
		exec(command_list, env, &status);
		// cleanup(command_list);
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
