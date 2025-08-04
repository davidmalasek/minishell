/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:57 by tomasklaus        #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/04 09:32:12 by dmalasek         ###   ########.fr       */
=======
/*   Updated: 2025/08/04 09:20:03 by tklaus           ###   ########.fr       */
>>>>>>> 832db7b (small changes in echo and exit)
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_flag_n(char **args, int *start)
{
	int	i;
	int	flag;
	int	j;

	i = 1;
	flag = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		if (args[i][j] == '\0')
			break ;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		flag = 1;
		i++;
	}
	*start = i;
	return (flag);
}

void	echo_print_args(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	start;
	int	flag;

	flag = echo_flag_n(args, &start);
	echo_print_args(args, start);
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
