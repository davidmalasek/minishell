/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:38:26 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 17:13:42 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_strtrim
** Removes leading and trailing characters specified in a set from a string
*/

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	i;
	int	e;

	i = 0;
	e = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]))
		i++;
	while (ft_strchr(set, s1[e]))
		e--;
	return (ft_substr(s1, i, e - i + 1));
}
