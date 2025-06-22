/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/22 11:48:07 by dmalasek         ###   ########.fr       */
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
void	exec(char **command)
{
	pid_t	child_pid;
	int		stat_loc;

	child_pid = fork();
	if (child_pid == 0)
	{
		execvp(command[0], command);
	}
	else
	{
		waitpid(child_pid, &stat_loc, WUNTRACED);
	}
}

int	main(void)
{
	char	*input;
	char	**command;

	while (1)
	{
		// read input
		input = readline("prompt> ");
		if (!input)
			break ;
		// parse, tokenize
		command = ft_split(input, ' ');
		// execute
		exec(command);
		free(input);
		free(command); // need double pointer free
	}
	return (EXIT_SUCCESS);
}
