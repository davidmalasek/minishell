/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:40:59 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 16:16:43 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_isascii
** Checks if the character is an ASCII value
*/

#include "libft.h"

int	ft_isascii(int character)
{
	if ((character >= 0 && character <= 127))
		return (1);
	else
		return (0);
}
