/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:08 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 11:35:57 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int del_arg(char *new_key, t_env *env)
{
    t_env *current = env;
    t_env *prev = NULL;

    // Find the node with matching key
    while (current)
    {
        if (ft_strcmp(current->key, new_key) == 0)
        {
            // Remove node from list
            if (prev)
                prev->next = current->next;
            // If removing head, do nothing to env pointer (caller must handle)
            // Free node
            free(current->key);
            free(current->value);
            free(current);
            return SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    // Not found
    return ERROR;
}

int ft_unset(char **args, t_env *env)
{
    if (validate_args(args, "unset") != SUCCESS) // can actually accept multiple args so change this
        return ERROR;

    int i = 1;
    while (args[i])
    {
        /* char *equal = ft_strchr(args[i], '='); // Find the position of '='
        if (!equal)
        {
            ft_putstr_fd("unset: invalid argument\n", 2);
            return (ERROR);
        }

        char *key = ft_substr(args[i], 0, equal - args[i]); // Extract key part before '=' */

        int status;
        status = del_arg(args[i], env);
        //free(key);
        if (status == ERROR)
            return ERROR;
        i++;
    }
    return SUCCESS;
}
