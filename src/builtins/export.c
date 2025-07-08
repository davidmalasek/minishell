/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:23 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/07 23:45:44 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
int new_arg(char *new_key, char *new_value, t_env *env)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (ERROR);

    new_node->key = ft_strdup(new_key);
    new_node->value = ft_strdup(new_value);
    new_node->exported = 1;
    new_node->next = NULL;

    // Add to end of list
    t_env *current = env;
    while (current->next)
        current = current->next;
    current->next = new_node;
    return SUCCESS;
}
int change_arg(char *new_key, char *new_value, t_env *env)
{
    t_env *current = env;

    // Search for existing key
    while (current)
    {
        if (ft_strcmp(current->key, new_key) == 0)
        {
            // Update existing value
            free(current->value);
            current->value = ft_strdup(new_value);
            current->exported = 1;
            return (SUCCESS);
        }
        current = current->next;
    }
    // If no match found, create new node
    return (new_arg(new_key, new_value, env));
}

int ft_export(char **args, t_env *env)
{
    if (!args[1])
        return (ft_env(args, env));
    int i = 1;
    while (args[i])
    {
        char *equal = ft_strchr(args[i], '='); // Find the position of '='
        if (!equal)
        {
            ft_putstr_fd("export: invalid argument\n", 2);
            return (ERROR);
        }

        char *key = ft_substr(args[i], 0, equal - args[i]); // Extract key part before '='
        char *value = ft_strdup(equal + 1);                 // Extract value part after '='
        int status;
        status = change_arg(key, value, env);
        free(key);
        free(value);
        //free(equal);
        if (status == ERROR)
            return ERROR;
        i++;
    }
    return SUCCESS;
}
