/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:58:01 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/30 22:35:47 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_pwd_from_cwd(t_env *env, char *key)
{
	t_env	*curr;
	char	cwd[PATH_MAX];

	curr = env;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = ft_strdup(cwd);
			if (!curr->value)
				return (ERROR);
			return (SUCCESS);
		}
		curr = curr->next;
	}
	if (add_env_node(&env, key, cwd, 1) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	ft_cd(char **args, t_env *env)
{
	if (!args[1])
	{
		ft_putstr_fd("cd: option not supported\n", 2);
		return (ERROR);
	}
	if (set_pwd_from_cwd(env, "OLDPWD") != SUCCESS)
		return (ERROR);
	if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("\n", 2);
		return (ERROR);
	}
	if (set_pwd_from_cwd(env, "PWD") != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
