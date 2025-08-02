/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:41:20 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/02 17:33:28 by tklaus           ###   ########.fr       */
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

	input = readline("minishell ➜ ");
	//printf("input: %s\n", input);
	if (input == NULL)
	{
		if (g_signal_interrupted)
		{
			g_signal_interrupted = 0;
			//printf("signal set to 0\n");
			return (NULL);
		}
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (input[0] == '\0')
	{
		//printf("marker\n");
		free(input);
		return (NULL);
	}
	add_history(input);
	return (input);
}

int	validate_input(char *input)
{
	char	*trimmed;
	int		len;

	if (!input || input[0] == '\0')
		return (0);
	trimmed = input;
	while (*trimmed && *trimmed == ' ')
		trimmed++;
	len = ft_strlen(trimmed);
	if (len == 0)
		return (0);
	if (trimmed[0] == '>' || trimmed[0] == '<' || trimmed[0] == '|')
	{
		printf("minishell: syntax error near unexpected token '%c'\n",
			trimmed[0]);
		return (0);
	}
	if ((trimmed[0] == '"' && len == 1) || (trimmed[0] == '\'' && len == 1))
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (0);
	}
	return (1);
}

int	handle_empty_or_signal(char *input)
{
	if (!input)
	{
		if (g_signal_interrupted)
		{
			g_signal_interrupted = 0;
			return (1);
		}
		return (1);
	}
	return (0);
}

int	handle_invalid_input(char *input)
{
	if (!validate_input(input))
	{
		free(input);
		return (1);
	}
	return (0);
}
