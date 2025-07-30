/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:27 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/30 22:35:50 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

int	ft_env(char **args, t_env *env)
{
	char	**envp;

	if (validate_args(args, "env", 1, 1) != SUCCESS)
		return (ERROR);
	envp = env_list_to_array(env);
	print_env(envp);
	return (SUCCESS);
}
