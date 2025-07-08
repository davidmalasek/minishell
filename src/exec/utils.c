/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:07:52 by tomasklaus        #+#    #+#             */
/*   Updated: 2025/07/07 23:22:14 by tomasklaus       ###   ########.fr       */
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


int no_redirs(t_command *command)
{
    if (!command)
        return EXIT_FAILURE;
    if (command->infile != NULL)
        return SUCCESS;
    if (command->outfile != NULL)
        return SUCCESS;
    if (command->append)
        return SUCCESS;
    if (command->heredoc_delimiter != NULL)
        return SUCCESS;
    if (command->pipe_to_next)
        return SUCCESS;
    return EXIT_FAILURE;
}

