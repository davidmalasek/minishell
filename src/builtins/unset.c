/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:08 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/14 17:41:25 by tklaus           ###   ########.fr       */
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

	status = 1;
	if (validate_args(args, "unset", -1, 2) != SUCCESS)
		return (ERROR);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			status = 0;
		}
		if (!del_arg(args[i], env))
			status = 0;
		i++;
	}
	if (status == 1)
		return (SUCCESS);
	else
		return (ERROR);
}
