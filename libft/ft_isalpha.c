/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:38 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 16:16:28 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isalpha
** Checks if the character is an alphabetic letter
*/

#include "libft.h"

int	ft_isalpha(int character)
{
	if ((character >= 65 && character <= 90) || (character >= 97
			&& character <= 122))
		return (1024);
	else
		return (0);
}
