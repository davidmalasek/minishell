/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:37:40 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 16:29:11 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_toupper
** Converts a lowercase letter to its uppercase equivalent
*/

#include "libft.h"

int	ft_toupper(int character)
{
	if (character >= 'a' && character <= 'z')
	{
		character -= 32;
	}
	return (character);
}
