/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:32:57 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 16:27:17 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strmapi
** Applies a function to each character of a string and returns a new string
*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*final_str;
	int		i;

	final_str = malloc(ft_strlen(s) + 1);
	if (!final_str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		final_str[i] = (*f)(i, s[i]);
		i++;
	}
	final_str[i] = '\0';
	return (final_str);
}
