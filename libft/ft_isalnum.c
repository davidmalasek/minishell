/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:38 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 16:16:17 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isalnum
** Checks if the character is alphanumeric
*/

#include "libft.h"

int	ft_isalnum(int character)
{
	if ((character >= 65 && character <= 90) || (character >= 97
			&& character <= 122) || (character >= 48 && character <= 57))
		return (8);
	else
		return (0);
}
