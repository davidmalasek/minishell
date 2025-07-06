/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:57 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 11:23:07 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_echo(char **args)
{
    int i;
    int flag;
    flag = 0;
    i = 1;
    if (args[1] && ft_strcmp(args[1], "-n") == 0)
    {
        i = 2;
        flag = 1;
    }

    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1] && args[i][0] != '\0')
				ft_putchar_fd(' ', 1);
        i++;
    }
    if (!flag)
        ft_putchar_fd('\n', 1);
    return (0);
}
