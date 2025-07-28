/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/08 22:11:43 by tomasklaus       ###   ########.fr       */
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
*/

t_env	*initialize_shell(char **envp)
{
	t_env	*env;

	env = load_env(envp);    // Copy env vars if needed
	setup_signal_handlers(); // Ctrl-C, Ctrl-\, Ctrl-D
	return (env);
}

int	main_loop(t_env *env)
{
	int			status;
	char		*input;
	t_command	*command_list;

	status = 0;
	while (1)
	{
		// this needs to be replaced by the proper structures
		input = readline("minishell ➜ ");
		if (input == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(EXIT_SUCCESS);
		}
		if (input && *input)
			add_history(input);
		command_list = parse(input); // Parse input into structured commands
		exec(command_list, env, &status);
		// cleanup(command_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = initialize_shell(envp);
	main_loop(env);
}
