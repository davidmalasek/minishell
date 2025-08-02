/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:57:27 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/08/02 14:43:13 by dmalasek         ###   ########.fr       */
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
	free_str_array(envp);
	return (SUCCESS);
}
