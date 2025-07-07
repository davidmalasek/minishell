/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:07:52 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/06 12:19:31 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *resolve_path(char *command)
{
    char *path = getenv("PATH");
    char **paths = ft_split(path, ':');
    int i = 0;
    while (paths[i])
    {
        char *full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(full_path, command);
        if (access(full_path, X_OK) == 0)
            return full_path;
        i++;
    }
    return NULL;
}
