/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:07:39 by davidmalase       #+#    #+#             */
/*   Updated: 2024/10/01 14:14:19 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strdup
** Duplicates a string by allocating memory and copying the content
*/

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		length;
	int		i;
	char	*new_str;

	length = 0;
	while (src[length])
		length++;
	new_str = malloc(length + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new_str[i] = src[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
