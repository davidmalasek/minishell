/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:25 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 11:30:53 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exit(char **args, int status)
{
    if (args && args[1])
    {
        ft_putstr_fd("exit: options not supported/n", 2);
        return (ERROR);
    }
    ft_putstr_fd("Quitting session", 1);
    exit(status);
    return SUCCESS;
}
