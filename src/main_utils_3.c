/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:58:42 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 10:00:29 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_continuation_input(char *initial_input)
{
	char	*continuation;
	char	*combined;
	char	*temp;

	continuation = readline("> ");
	if (!continuation)
	{
		free(initial_input);
		return (NULL);
	}
	temp = ft_strjoin(initial_input, " ");
	combined = ft_strjoin(temp, continuation);
	free(temp);
	free(continuation);
	free(initial_input);
	return (combined);
}
