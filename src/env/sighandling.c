/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:25:18 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/02 17:33:01 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);
	g_signal_interrupted = 1;
	if (rl_line_buffer)
	{
		rl_line_buffer[0] = '\0';
		rl_point = 0;
		rl_end = 0;
	}
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_child(int signo)
{
	(void)signo;
	printf("hello");
	ft_putstr_fd("\b\b  ", 2);     // Erase ^C characters
    ft_putstr_fd("\n", 2);         // New line
	exit(130); // 130 is the conventional exit code for SIGINT
}

int	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}
