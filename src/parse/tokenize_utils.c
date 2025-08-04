/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:48:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 11:09:08 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Looks up the value of an environment variable.
 */
char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * Expands a variable token (e.g., $HOME or $?).
 */
char	*expand_variable(char *token, t_env *env, int last_exit_status)
{
	char	*key;
	char	*value;

	if (ft_strcmp(token, "$?") == 0)
		return (ft_itoa(last_exit_status));
	if (token[0] == '$' && token[1] != '\0')
	{
		key = ft_strdup(token + 1);
		value = get_env_value(env, key);
		free(key);
		if (value)
			return (ft_strdup(value));
		return (ft_strdup(""));
	}
	return (ft_strdup(token));
}

/**
 * Checks if a token is single-quoted.
 */
int	is_single_quoted(char *component)
{
	int	len;

	if (!component)
		return (0);
	len = ft_strlen(component);
	return (len >= 2 && component[0] == '\'' && component[len - 1] == '\'');
}

/**
 * Removes surrounding quotes from a token.
 */
char	*remove_quotes(char *component)
{
	int		len;
	char	*result;

	len = ft_strlen(component);
	if (len >= 2 && ((component[0] == '\'' && component[len - 1] == '\'')
			|| (component[0] == '"' && component[len - 1] == '"')))
	{
		result = ft_substr(component, 1, len - 2);
		return (result);
	}
	return (ft_strdup(component));
}

/**
 * Checks if a token is double-quoted.
 */
int	is_double_quoted(char *component)
{
	int	len;

	if (!component)
		return (0);
	len = ft_strlen(component);
	return (len >= 2 && component[0] == '"' && component[len - 1] == '"');
}
