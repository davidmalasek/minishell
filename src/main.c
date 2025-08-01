/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:30:36 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/01 21:01:01 by dmalasek         ###   ########.fr       */
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

DAVID
- single quotes
- heredoc stale nefunguje
*/

int		g_signal_interrupted = 0;

t_env	*initialize_shell(char **envp)
{
	t_env	*env;

	env = load_env(envp);
	setup_signal_handlers();
	return (env);
}

void	print_command(t_command *command_list)
{
	int			i;
	t_command	*cmd;

	cmd = command_list;
	while (cmd && cmd->args)
	{
		printf("---- Command ----\n");
		printf("args: ");
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("'%s' ", cmd->args[i]);
				i++;
			}
		}
		else
		{
			printf("(none)");
		}
		printf("\n");
		printf("infile: ");
		if (cmd->infile)
			printf("'%s'\n", cmd->infile);
		else
			printf("(none)\n");
		printf("outfile: ");
		if (cmd->outfile)
			printf("'%s'\n", cmd->outfile);
		else
			printf("(none)\n");
		printf("heredoc_delim: ");
		if (cmd->heredoc_delim)
			printf("'%s'\n", cmd->heredoc_delim);
		else
			printf("(none)\n");
		printf("append: %d\n", cmd->append);
		printf("pipe_to_next: %d\n", cmd->pipe_to_next);
		printf("-----------------\n");
		cmd++;
	}
}

char	*get_input(void)
{
	char	*input;

	g_signal_interrupted = 0;
	input = readline("minishell ➜ ");
	if (input == NULL)
	{
		if (g_signal_interrupted)
		{
			g_signal_interrupted = 0;
			return (NULL);
		}
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

int	main_loop(t_env *env)
{
	int			status;
	char		*input;
	t_command	*command_list;

	status = 0;
	while (1)
	{
		input = get_input();
		if (!input)
		{
			if (g_signal_interrupted)
			{
				g_signal_interrupted = 0;
				continue ;
			}
			continue ;
		}
		if (!validate_input(input))
		{
			free(input);
			continue ;
		}
		if (status == ECHON)
		{
			ft_putchar_fd('\n', 1);
			status = 0;
		}
		command_list = parse(input, env, status);
		if (!command_list)
		{
			free(input);
			continue ;
		}
		// print_command(command_list);
		exec(command_list, env, &status);
		cleanup_commands(command_list);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = initialize_shell(envp);
	main_loop(env);
	cleanup_env(env);
	return (0);
}
