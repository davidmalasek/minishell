/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/05/15 22:47:06 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
Create an infinite loop that displays a prompt and accepts input via readline()
Read the line and store it in a buffer
Divide the characters separated by spaces (and other delimiters) into multiple strings
Tokenize the individual words - classify into categories like WORDS and PIPES (thats Lex)?
Go through those tokens and make a command table according to a grammar (thats Yacc)?
Once the table is completed, execute the commands
	its either a built in function that we can program
		◦ echo with option -n
		◦ cd with only a relative or absolute path
		◦ pwd with no options
		◦ export with no options
		◦ unset with no options
		◦ env with no options or arguments
		◦ exit with no options
		
	or we have to fork and use execvo
		◦ for stuff like ls etc

------------------also--------------------------------
manage history
global variable - signals?
manage quotes (''""), environment variables (${}), $?, ctrl-C, ctrl-D and ctrl-\ 
 */


//this is a test to see how forking works
int main(int ac, char **av)
{
	(void)ac;
	int status;

	if (fork() == 0)
	{
		execvp(av[1], av + 1);
	}

	wait(&status);
	return (0);
}