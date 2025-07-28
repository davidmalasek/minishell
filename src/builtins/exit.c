/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:25 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/08 22:09:50 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exit(char **args, int status)
{
    if (validate_args(args, "exit", 2, 1) != SUCCESS)
        return ERROR;
    if (args && args[1])
        status = ft_atoi(args[1]);
    ft_putstr_fd("Quitting session\n", 1);
    exit(status);
    return status;
}
