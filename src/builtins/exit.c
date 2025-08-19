/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:25 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/19 16:53:18 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char **args, int status, t_exec_context exec_context)
{
	int	error;

	error = 0;
	if (args && args[1])
	{
		if ((args[1][0] == '-' || args[1][0] == '+') && args[1][1] == '\0')
			error = 1;
		else
			status = ft_safe_atoi(args[1], &error);
		if (error)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			status = 2;
		}
	}
	if (validate_args(args, "exit", 2, 1) && !error)
		return (ERROR);
	ft_putstr_fd("Quitting session\n", 1);
	exit_shell(exec_context.command_list, *exec_context.env, status);
	return (status);
}
