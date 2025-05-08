/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:08:00 by davidmalase       #+#    #+#             */
/*   Updated: 2025/01/29 17:41:04 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Works as ordinary ft_atoi and returns an
 * error if the number is larger of smaller than int range.
 */
int	ft_safe_atoi(const char *str, int *error)
{
	long	res;
	int		positive;

	positive = 1;
	res = 0;
	*error = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			positive = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((res * positive) > 2147483647 || ((res * positive) < -2147483648))
			return (*error = 1, 0);
		str++;
	}
	if (*str != '\0')
		*error = 1;
	return ((int)(res * positive));
}
