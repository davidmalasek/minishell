/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/11 15:46:28 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	cleanup_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	if (!env)
		return ;
	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void	cleanup_commands(t_command *command_list)
{
	int	i;

	i = 0;
	if (!command_list)
		return ;
	while (command_list[i].args)
	{
		cleanup_single_command(&command_list[i]);
		i++;
	}
	free(command_list);
}

void	cleanup_tokens(t_token *tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].type != -1)
	{
		if (tokens[i].value)
			free(tokens[i].value);
		i++;
	}
	free(tokens);
}

void	exit_shell(t_command *command_list, t_env *env, int exit_code)
{
	if (command_list)
		cleanup_commands(command_list);
	if (env)
		cleanup_env(env);
	exit(exit_code);
}
