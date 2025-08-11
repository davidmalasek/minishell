/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:23 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/11 16:11:47 by tomasklaus       ###   ########.fr       */
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

char	*remove_all_quotes(const char *arg)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(arg) + 1);
	if (!res)
		return (NULL);
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '\"')
			res[j++] = arg[i++];
		else
			i++;
	}
	res[j] = '\0';
	return (res);
}

static int	export_one(char *arg, t_env *env)
{
	char	*equal;
	char	*key;
	char	*value;
	int		status;
	char	*clean_arg;

	clean_arg = remove_all_quotes(arg);
	equal = ft_strchr(clean_arg, '=');
	if (!equal)
	{
		if (is_valid_identifier(clean_arg))
			return (SUCCESS);
		return (printf("export: invalid identifier: %s\n", clean_arg), ERROR);
	}
	if (equal == clean_arg)
		return (printf("export: invalid identifier: %s\n", clean_arg), ERROR);
	key = ft_substr(clean_arg, 0, equal - clean_arg);
	if (!is_valid_identifier(key))
		return (printf("export: invalid identifier: %s\n", clean_arg),
			free(key), ERROR);
	value = ft_strdup(equal + 1);
	status = change_arg(key, value, env);
	return (free(key), free(value), free(clean_arg), status);
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
