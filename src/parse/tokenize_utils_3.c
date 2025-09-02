/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:05:45 by dmalasek          #+#    #+#             */
/*   Updated: 2025/09/02 12:37:58 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Expands the contents of a double-quoted
 * substring and copies the result into the output buffer.
 */
void	expand_copy_double(const char *component, size_t ij[2], void **bundle,
		size_t *w)
{
	char	*quoted_segment;
	char	*expanded;
	size_t	elen;

	quoted_segment = ft_substr(component, ij[0], ij[1] - ij[0] + 1);
	if (quoted_segment)
	{
		expanded = expand_in_double_quotes(quoted_segment, (t_env *)bundle[0],
				*(int *)bundle[2]);
		free(quoted_segment);
		if (expanded)
		{
			elen = ft_strlen(expanded);
			ft_memcpy((char *)bundle[1] + *w, expanded, elen);
			*w += elen;
			free(expanded);
		}
	}
}

/**
 * Processes a single-quoted segment by copying
 * its contents into the result and returning the
 * next index to continue parsing.
 */
size_t	process_single(const char *c, size_t i, char *res, size_t *w)
{
	size_t	len;
	size_t	j;
	size_t	range[2];

	len = ft_strlen(c);
	j = find_end(c, i, len, '\'');
	if (j > i + 1)
	{
		range[0] = i + 1;
		range[1] = j;
		copy_inner(res, w, c, range);
	}
	if (j >= len)
		return (len);
	return (j + 1);
}

/**
 * Processes a double-quoted segment by expanding
 * its contents and copying the result into the output
 * buffer, then returns the next parsing index.
 */
size_t	process_double(const char *c, size_t i, void **bundle, size_t *w)
{
	size_t	len;
	size_t	j;
	size_t	ij[2];

	len = ft_strlen(c);
	j = find_end(c, i, len, '\"');
	if (j >= i + 1)
	{
		ij[0] = i;
		ij[1] = j;
		expand_copy_double(c, ij, bundle, w);
	}
	if (j >= len)
		return (len);
	return (j + 1);
}

/**
 * Removes quote delimiters from a string, expanding
 * double-quoted segments and copying the processed
 * content into a new buffer.
 */
char	*remove_quote_delimiters(const char *comp, t_env *env, int last_exit)
{
	size_t	i;
	size_t	write_idx;
	void	*bundle[3];
	char	*res;

	if (!comp)
		return (NULL);
	res = malloc(ft_strlen(comp) + 1);
	if (!res)
		return (NULL);
	i = 0;
	write_idx = 0;
	bundle[0] = env;
	bundle[1] = res;
	bundle[2] = &last_exit;
	while (i < ft_strlen(comp))
	{
		if (comp[i] == '\'')
			i = process_single(comp, i, res, &write_idx);
		else if (comp[i] == '\"')
			i = process_double(comp, i, bundle, &write_idx);
		else
			res[write_idx++] = comp[i++];
	}
	return (res[write_idx] = '\0', res);
}

/**
 * Processes a word token by handling quotes or
 * variable expansion and returns the resulting string.
 */
char	*process_word_token(char *component, t_env *env, int last_exit_status)
{
	if (!component)
		return (NULL);
	if (is_double_quoted(component))
		return (expand_in_double_quotes(component, env, last_exit_status));
	if (component[0] == '$')
		return (handle_variable_component(component, env, last_exit_status));
	if (ft_strchr(component, '\'') || ft_strchr(component, '\"'))
		return (remove_quote_delimiters(component, env, last_exit_status));
	return (remove_quotes(component));
}
