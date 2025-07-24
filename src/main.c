/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/24 10:40:07 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
Create an infinite loop that displays a prompt and accepts input via readline()
Read the line and store it in a buffer
Divide the characters separated by spaces (and other delimiters) into multiple strings
Tokenize the individual words
	- classify into categories like WORDS and PIPES (thats Lex)?
Go through those tokens and make a command table according to a grammar (thats Yacc)?
Once the table is completed, execute the commands

------------------also--------------------------------
manage history
global variable - signals?
manage quotes (''""), environment variables (${}), $?, ctrl-C, ctrl-D and ctrl-\
 */

/*
either a built in function that we can program (named in the subject)
	◦ echo with option -n
	◦ cd with only a relative or absolute path
	◦ pwd with no options
	◦ export with no options
	◦ unset with no options
	◦ env with no options or arguments
	◦ exit with no options

or we have to fork and use execve
	◦ for stuff like ls etc
 */

t_env	*initialize_shell(char **envp)
{
	t_env	*env;

	env = load_env(envp); // Copy env vars if needed
	// setup_signal_handlers(); // Ctrl-C, Ctrl-\, Ctrl-D
	// init_history();				// Optional: readline history
	return (env);
}

int	main_loop(t_env *env)
{
	char		*input;
	t_command	*command_list;

	while (1)
	{
		// this needs to be replaced by the proper structures
		input = readline("minishell ➜ ");
		if (input && *input)
			add_history(input);
		// add_to_history(input);
		// TODO TOMÁŠ: tady potřebuju abys mi předal ten last_exit_status
		command_list = parse(input, env, last_exit_status);
		// Parse input into structured commands
		exec(command_list, env);
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
