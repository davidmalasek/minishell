/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:13:50 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 16:41:13 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strrchr
** Locates the last occurrence of a character in a string
*/

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*last_occurrence;

	last_occurrence = ft_strlen(str) + str;
	while (last_occurrence >= str && *last_occurrence != (char)c)
		last_occurrence--;
	if (last_occurrence >= str)
		return ((char *)last_occurrence);
	else
		return (NULL);
}
