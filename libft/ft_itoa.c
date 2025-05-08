/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:45:43 by dmalasek          #+#    #+#             */
/*   Updated: 2024/10/03 10:17:06 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_itoa
** Converts an integer to a null-terminated string
*/

#include "libft.h"

int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

void	ft_putnbr(int nb, char *str, int *index)
{
	if (nb < 0)
	{
		str[(*index)++] = '-';
		if (nb == -2147483648)
		{
			nb = -(nb / 10);
			ft_putnbr(nb, str, index);
			str[(*index)++] = '8';
			return ;
		}
		nb = -nb;
	}
	if (nb / 10 != 0)
		ft_putnbr(nb / 10, str, index);
	str[(*index)++] = (nb % 10) + '0';
}

char	*ft_itoa(int n)
{
	int		digits;
	int		index;
	int		add_byte;
	char	*final_str;

	if (n < 0)
		add_byte = 1;
	else
		add_byte = 0;
	digits = count_digits(n);
	final_str = malloc(digits + add_byte + 1);
	index = 0;
	if (!final_str)
		return (NULL);
	ft_putnbr(n, final_str, &index);
	final_str[index] = '\0';
	return (final_str);
}
