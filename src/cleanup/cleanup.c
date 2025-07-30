/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:00:00 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/30 22:35:56 by tomasklaus       ###   ########.fr       */
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
	int	j;

	if (!command_list)
		return ;
	i = 0;
	while (command_list[i].args)
	{
		j = 0;
		while (command_list[i].args[j])
		{
			free(command_list[i].args[j]);
			j++;
		}
		free(command_list[i].args);
		if (command_list[i].infile)
			free(command_list[i].infile);
		if (command_list[i].outfile)
			free(command_list[i].outfile);
		if (command_list[i].heredoc_delimiter)
			free(command_list[i].heredoc_delimiter);
		i++;
	}
	free(command_list);
}

void	cleanup_shell(t_command *command_list, t_env *env)
{
	cleanup_commands(command_list);
	cleanup_env(env);
	clear_history();
}
