/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklaus <tklaus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:25:18 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/15 12:07:47 by tklaus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signo)
{
	(void)signo;
	g_signal_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
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
	g_signal_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_line_buffer)
	{
		rl_line_buffer[0] = '\0';
		rl_point = 0;
		rl_end = 0;
	}
	rl_on_new_line();
}

int	setup_signal_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}
