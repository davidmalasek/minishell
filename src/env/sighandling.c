/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 21:25:18 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/28 23:52:52 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Declare global variable defined in main.c
extern int g_signal_interrupted;

void sigint_handler(int signo)
{
    (void)signo;
    write(STDOUT_FILENO, "\n", 1);

    // Set a global flag to indicate interruption by SIGINT
    g_signal_interrupted = 1;

    // Workaround to clear the current input line bc rl_replace_line is unavailable:
    if (rl_line_buffer)
    {
        rl_line_buffer[0] = '\0';
        rl_point = 0;
        rl_end = 0;
    }
    rl_on_new_line();
}

int setup_signal_handlers()
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);

    return SUCCESS;
}
