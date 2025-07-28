/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:57 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/28 21:53:30 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int echo_flag_n(char **args, int *start)
{
    int i = 1;
    int flag = 0;

    // Accept multiple -n, -nnn, etc.
    while (args[i] && args[i][0] == '-')
    {
        int j = 1;
        if (args[i][j] == '\0')
            break;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] != '\0')
            break;
        flag = 1;
        i++;
    }
    *start = i;
    return flag;
}

static void echo_print_args(char **args, int start)
{
    int i = start;
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
}

int ft_echo(char **args)
{
    int start;
    int flag;

    flag = echo_flag_n(args, &start);
    echo_print_args(args, start);
    if (!flag)
    {
        ft_putchar_fd('\n', 1);
        return 0;
    }
    return (69);
}
 
