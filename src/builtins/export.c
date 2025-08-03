/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:23 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/03 18:49:47 by dmalasek         ###   ########.fr       */
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

static int	is_valid_identifier(char *key)
{
	int	i;

	if (!key || key[0] == '\0')
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	export_one(char *arg, t_env *env)
{
	char	*equal;
	char	*key;
	char	*value;
	int		status;
	char	*clean_value;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		if (is_valid_identifier(arg))
			return (SUCCESS);
		return (printf("export: invalid identifier: %s\n", arg), ERROR);
	}
	if (equal == arg)
		return (printf("export: invalid identifier: %s\n", arg), ERROR);
	key = ft_substr(arg, 0, equal - arg);
	if (!is_valid_identifier(key))
		return (printf("export: invalid identifier: %s\n", arg), free(key),
			ERROR);
	value = ft_strdup(equal + 1);
	clean_value = remove_quotes(value);
	status = change_arg(key, clean_value, env);
	return (free(key), free(value), free(clean_value), status);
}

int	ft_export(char **args, t_env *env)
{
	int	i;
	int	status;
	int	overall_status;

	if (!args[1])
		return (ft_env(args, env));
	i = 1;
	overall_status = SUCCESS;
	while (args[i])
	{
		status = export_one(args[i], env);
		if (status == ERROR)
			overall_status = ERROR;
		i++;
	}
	return (overall_status);
}
