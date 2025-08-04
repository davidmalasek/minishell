/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:05:45 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 11:07:04 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Returns the token type for shell operators (|, <, >, etc.).
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
 * Handles a single-quoted string.
 */
char	*handle_single_quoted(char *component)
{
	return (remove_quotes(component));
}

/**
 * Handles a double-quoted string.
 */
char	*handle_double_quoted(char *component, t_env *env, int last_exit_status)
{
	return (expand_in_double_quotes(component, env, last_exit_status));
}

/**
 * Handles a token that starts with $.
 */
char	*handle_variable_component(char *component, t_env *env,
		int last_exit_status)
{
	if (ft_strcmp(component, "$?") == 0)
		return (ft_itoa(last_exit_status));
	return (expand_variable(component, env, last_exit_status));
}

/**
 * Processes a word token, handling quotes and variable expansion.
 */
char	*process_word_token(char *component, t_env *env, int last_exit_status)
{
	if (is_single_quoted(component))
		return (handle_single_quoted(component));
	if (is_double_quoted(component))
		return (handle_double_quoted(component, env, last_exit_status));
	if (component[0] == '$')
		return (handle_variable_component(component, env, last_exit_status));
	return (remove_quotes(component));
}
