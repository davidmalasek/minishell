/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:41:20 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/03 18:53:39 by tklaus           ###   ########.fr       */
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

int	validate_input(char *input)
{
	char	*trimmed;
	int		len;
	int		i;
	int		pipe_found;

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
	if (trimmed[0] == '"' && len == 1)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (0);
	}
	if (trimmed[0] == '\'' && len == 1)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (0);
	}
	// Check for consecutive pipes or trailing pipes
	i = 0;
	pipe_found = 0;
	while (i < len)
	{
		if (trimmed[i] == '|')
		{
			if (pipe_found)
			{
				printf("minishell: syntax error near unexpected token '|'\n");
				return (0);
			}
			pipe_found = 1;
		}
		else if (trimmed[i] != ' ')
			pipe_found = 0;
		i++;
	}
	if (pipe_found)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (0);
	}
	return (1);
}

int	handle_empty_or_signal(char *input, int *status)
{
	if (g_signal_interrupted)
	{
		*status = 130;
		g_signal_interrupted = 0; //nejdriv otestovat, mozna bude potreba vymazat
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
