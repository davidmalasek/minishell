/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:41:20 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/03 19:14:46 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*initialize_shell(char **envp)
{
	t_env	*env;

	env = load_env(envp);
	setup_signal_handlers();
	return (env);
}

char	*get_input(void)
{
	char	*input;

	g_signal_interrupted = 0;
	input = readline("minishell ➜ ");
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	add_history(input);
	return (input);
}

int	handle_empty_or_signal(char *input, int *status)
{
	if (g_signal_interrupted)
	{
		*status = 130;
		g_signal_interrupted = 0; //mozna vymazat po testovani
	}
	if (!input)
		return (1);
	return (0);
}

int	handle_invalid_input(char *input, int *status)
{
	if (!validate_input(input))
	{
		*status = 2;
		free(input);
		return (1);
	}
	return (0);
}
