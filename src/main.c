/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/22 13:11:30 by tomasklaus       ###   ########.fr       */
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


void initialize_shell(char **envp)
{
	setup_signal_handlers(); // Ctrl-C, Ctrl-\, Ctrl-D
	load_environment();		 // Copy env vars if needed
	init_history();			 // Optional: readline history
}

int main_loop()
{
	while (1)
	{
		//this needs to be replaced by the proper structures
		char *input;
		char **command_table;

		input = readline("prompt> ");

		add_to_history(input);

		tokens = lexer(input); // Tokenize input into symbols: WORD, PIPE, REDIRECT, etc.

		command_table = parser(tokens); // Parse tokens into structured commands
		
		exec(command_table); // Execute commands (pipeline, built-ins, execve, etc.)

		cleanup(tokens, command_table);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	

	initialize_shell(envp);
	main_loop();
}
