/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:27 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 10:52:51 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void print_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        ft_putstr_fd(envp[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
}

int ft_env(char **args, t_env *env)
{
    if (args && args[1])
    {
        ft_putstr_fd("env: options not supported", 2);
        return (ERROR);
    }
    char **envp;

    envp = env_list_to_array(env);
    print_env(envp);
    return SUCCESS;
}
