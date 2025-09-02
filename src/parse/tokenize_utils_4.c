/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:37:40 by dmalasek          #+#    #+#             */
/*   Updated: 2025/09/02 12:39:46 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Determines the token type corresponding to a shell operator string.
 */
int	get_operator_token_type(char *component)
{
	if (ft_strcmp(component, "|") == 0)
		return (PIPE);
	if (ft_strcmp(component, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(component, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(component, ">>") == 0)
		return (APPEND_OUT);
	if (ft_strcmp(component, ">") == 0)
		return (REDIR_OUT);
	return (-1);
}

/**
 * Expands a variable reference, handling `$?` as the
 * last exit status or other names via environment lookup.
 */
char	*handle_variable_component(char *component, t_env *env,
		int last_exit_status)
{
	if (ft_strcmp(component, "$?") == 0)
		return (ft_itoa(last_exit_status));
	return (expand_variable(component, env, last_exit_status));
}

/**
 * Finds the index of the next occurrence
 * of a given quote character in a string.
 */
size_t	find_end(const char *s, size_t i, size_t len, char q)
{
	size_t	j;

	j = i + 1;
	while (j < len && s[j] != q)
		j++;
	return (j);
}

/**
 * Copies a substring from the source
 * into the destination buffer and advances the write index.
 */
void	copy_inner(char *dst, size_t *w, const char *src, size_t range[2])
{
	size_t	n;

	n = range[1] - range[0];
	ft_memcpy(dst + *w, src + range[0], n);
	*w += n;
}
