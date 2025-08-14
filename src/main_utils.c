/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:41:20 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/14 17:41:39 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Initializes the shell environment and sets up signal handlers.
 */
t_env	*initialize_shell(char **envp)
{
	t_env	*env;

	env = load_env(envp);
	setup_signal_handlers();
	return (env);
}
/**
 * Reads user input from the terminal, handles EOF, empty input,
 *	and line continuation.
 * Handles the following cases with if statements:
 *   - if (input == NULL): Checks for EOF (Ctrl+D), exits the shell.
 *   - if (input[0] == '\0'): Checks for empty input (just Enter), returns NULL.
 *   - while (needs_continuation(input)): Checks if input needs continuation,
 *	prompts for more input.
 * Adds valid input to history.
 * @return The input string, or NULL if input is empty or interrupted.
 */

char	*get_input(t_env *env)
{
	char	*input;

	g_signal_interrupted = 0;
	input = readline("minishell ➜ ");
	if (input == NULL)
	{
		write(STDOUT_FILENO, "exit\n", 5);
		exit_shell(NULL, env, 2);
	}
	if (input[0] == '\0')
	{
		free(input);
		return (NULL);
	}
	while (needs_continuation(input))
	{
		input = get_continuation_input(input);
		if (!input)
			return (NULL);
	}
	add_history(input);
	return (input);
}

/**
 * Checks whether the provided input string contains only whitespace characters
 * (spaces and tabs), indicating that the input is effectively empty.
 * Checks if a signal (such as SIGINT or SIGQUIT)
 * was received during input processing
 *
 * Checks if the input is empty (spaces/tabs only) or if a signal was received.
 * @return 1 if input should be skipped, 0 otherwise.
 */
int	handle_empty_or_signal(char *input, int *status)
{
	int	i;

	if (input && input[0] != '\0')
	{
		i = 0;
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (input[i] == '\0')
		{
			*status = 0;
			free(input);
			return (1);
		}
	}
	if (g_signal_interrupted)
	{
		*status = 130;
		g_signal_interrupted = 0;
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
