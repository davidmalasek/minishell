/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:25:05 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/04 11:58:56 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_exported(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->exported)
			count++;
		env = env->next;
	}
	return (count);
}

/**
 * Converts the exported environment variables
 * from the linked list to an array of strings.
 * Each string is in the format "KEY=VALUE".
 */

char	**env_list_to_array(t_env *env)
{
	int		count;
	char	**envp;
	int		i;

	count = count_exported(env);
	envp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (env)
	{
		if (env->exported)
		{
			envp[i++] = ft_strjoin3(env->key, "=", env->value);
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

static t_env	*create_env_node(char *key, char *value, int exported)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = ft_strdup(value);
	if (!new_node->value)
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}
	new_node->exported = exported;
	new_node->next = NULL;
	return (new_node);
}

int	add_env_node(t_env **head, char *key, char *value, int exported)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_env_node(key, value, exported);
	if (!new_node)
		return (ERROR);
	if (!*head)
	{
		*head = new_node;
		return (SUCCESS);
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (SUCCESS);
}

/**
 * Loads environment variables from an array of strings into a linked list.
 * Only variables containing '=' are added and marked as exported.
 *
 * @param envp Array of environment strings (NULL-terminated).
 * @return Pointer to the head of the environment variable list.
 */
t_env	*load_env(char **envp)
{
	t_env	*head;
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (!equal)
		{
			i++;
			continue ;
		}
		key = ft_substr(envp[i], 0, equal - envp[i]);
		value = ft_strdup(equal + 1);
		add_env_node(&head, key, value, 1);
		free(key);
		free(value);
		i++;
	}
	return (head);
}
