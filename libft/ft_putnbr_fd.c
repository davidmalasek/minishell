/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:58:21 by dmalasek          #+#    #+#             */
/*   Updated: 2024/09/30 17:26:21 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_putnbr_fd
** Outputs an integer to the given file descriptor
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	minus_sign;
	char	string;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	minus_sign = '-';
	if (n < 0)
	{
		write(fd, &minus_sign, 1);
		n = -n;
	}
	if (n / 10 != 0)
		ft_putnbr_fd(n / 10, fd);
	string = (n % 10) + '0';
	write(fd, &string, 1);
}
