/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:08 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/07 23:47:53 by tomasklaus       ###   ########.fr       */
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
    if (validate_args(args, "unset", -1, 2) != SUCCESS)
        return ERROR;

    int i = 1;
    while (args[i])
    {
        int status;
        status = del_arg(args[i], env);
        if (status == ERROR)
            return ERROR;
        i++;
    }
    return SUCCESS;
}
