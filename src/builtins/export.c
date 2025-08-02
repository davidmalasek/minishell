/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:23 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/02 11:42:39 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	new_arg(char *new_key, char *new_value, t_env *env)
{
	t_env	*new_node;
	t_env	*current;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (ERROR);
	new_node->key = ft_strdup(new_key);
	new_node->value = ft_strdup(new_value);
	new_node->exported = 1;
	new_node->next = NULL;
	current = env;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (SUCCESS);
}

int	change_arg(char *new_key, char *new_value, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, new_key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			current->exported = 1;
			return (SUCCESS);
		}
		current = current->next;
	}
	return (new_arg(new_key, new_value, env));
}

static int	export_one(char *arg, t_env *env)
{
	char	*equal;
	char	*key;
	char	*value;
	int		status;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		ft_putstr_fd("export: invalid argument\n", 2);
		return (ERROR);
	}
	key = ft_substr(arg, 0, equal - arg);
	value = ft_strdup(equal + 1);
	status = change_arg(key, value, env);
	free(key);
	free(value);
	return (status);
}

int	ft_export(char **args, t_env *env)
{
	int	i;
	int	status;

	if (!args[1])
		return (ft_env(args, env));
	i = 1;
	while (args[i])
	{
		status = export_one(args[i], env);
		if (status == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
