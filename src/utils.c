/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 13:29:04 by dmalasek          #+#    #+#             */
/*   Updated: 2025/06/22 13:29:39 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	get_array_length(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
	{
		len++;
	}
	return (len);
}
