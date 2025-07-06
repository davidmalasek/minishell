/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:07:22 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 11:37:07 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int arg_count(char **args)
{
    int count = 0;
    while (args && args[count])
        count++;
    return count;
}

int validate_args(char **args, char *command_name)
{
    int arg_count_val = arg_count(args);

    if (!args || !args[0])
    {
        ft_putstr_fd(command_name, 2);
        ft_putstr_fd(": no arguments provided/n", 2);
        return ERROR;
    }

    if (arg_count_val < 2)
    {
        ft_putstr_fd(command_name, 2);
        ft_putstr_fd(": too few arguments/n", 2);
        return ERROR;
    }

    if (arg_count_val > 2)
    {
        ft_putstr_fd(command_name, 2);
        ft_putstr_fd(": too many arguments/n", 2);
        return ERROR;
    }

    return SUCCESS;
}
