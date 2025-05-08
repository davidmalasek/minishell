/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:41:58 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 17:26:08 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strchr
** Locates the first occurrence of a character in a string
*/

#include "libft.h"

char	*ft_strchr(const char *string, int character)
{
	unsigned char	unsigned_char;

	unsigned_char = (unsigned char)character;
	while (*string)
	{
		if ((unsigned char)*string == unsigned_char)
			return ((char *)string);
		string++;
	}
	if (unsigned_char == '\0')
		return ((char *)string);
	return (NULL);
}
