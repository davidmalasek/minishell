/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:08 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/30 22:35:54 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	del_arg(char *new_key, t_env *env)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, new_key) == 0)
		{
			if (prev)
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (ERROR);
}

int	ft_unset(char **args, t_env *env)
{
	int	i;
	int	status;

	if (validate_args(args, "unset", -1, 2) != SUCCESS)
		return (ERROR);
	i = 1;
	while (args[i])
	{
		status = del_arg(args[i], env);
		if (status == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
