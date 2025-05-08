/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:15:29 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 17:23:54 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strnstr
** Locates the first occurrence of a substring (l - little)
** in a string (b - big), searching up to a specified length
*/

#include "libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	i;
	size_t	e;

	i = 0;
	if (*l == '\0')
		return ((char *)b);
	while (i < len && b[i] != '\0')
	{
		if (b[i] == l[0])
		{
			e = 0;
			while ((l[e] != '\0') && ((i + e) < len) && (b[i + e] == l[e]))
				e++;
			if (l[e] == '\0')
				return ((char *)&b[i]);
		}
		i++;
	}
	return (NULL);
}
