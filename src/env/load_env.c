/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 22:25:05 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/05 14:58:50 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
    char *tmp;
    char *result;

    if (!s1 || !s2 || !s3)
        return (NULL);
    tmp = ft_strjoin(s1, s2);
    if (!tmp)
        return (NULL);
    result = ft_strjoin(tmp, s3);
    free(tmp);
    return (result);
}

int count_exported(t_env *env)
{
    int count = 0;
    while (env)
    {
        if (env->exported)
            count++;
        env = env->next;
    }
    return count;
}

char **env_list_to_array(t_env *env)
{
    int count = count_exported(env);
    char **envp = malloc(sizeof(char *) * (count + 1));
    int i = 0;

    while (env)
    {
        if (env->exported)
        {
            envp[i++] = ft_strjoin3(env->key, "=", env->value);
        }
        env = env->next;
    }
    envp[i] = NULL;
    return envp;
}

int add_env_node(t_env **head, char *key, char *value, int exported)
{
    t_env *new_node;
    t_env *current;

    // Allocate memory for the new node
    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return ERROR;

    // Duplicate the key string
    new_node->key = ft_strdup(key);
    if (!new_node->key)
    {
        free(new_node);
        return ERROR;
    }

    // Duplicate the value string
    new_node->value = ft_strdup(value);
    if (!new_node->value)
    {
        free(new_node->key);
        free(new_node);
        return ERROR;
    }

    // Set exported flag and next pointer
    new_node->exported = exported;
    new_node->next = NULL;

    // If the list is empty, set new node as head
    if (!*head)
    {
        *head = new_node;
        return SUCCESS;
    }

    // Otherwise, append to the end of the list
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return SUCCESS;
}

t_env *load_env(char **envp)
{
    t_env *head = NULL;

    int i = 0;
    while (envp[i])
    {
        char *equal = ft_strchr(envp[i], '='); // Find the position of '='
        if (!equal)
        {
            i++;
            continue;
        }

        char *key = ft_substr(envp[i], 0, equal - envp[i]); // Extract key part before '='
        char *value = ft_strdup(equal + 1);                 // Extract value part after '='
        add_env_node(&head, key, value, 1);
        free(key);
        free(value);
        i++;
    }
    return head;
}