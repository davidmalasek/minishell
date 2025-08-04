/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:03:38 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 11:08:09 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Extracts the content inside quotes.
 */
char	*extract_quoted_content(char *component)
{
	char	*content;
	int		len;

	len = ft_strlen(component);
	content = ft_substr(component, 1, len - 2);
	if (!content)
		return (ft_strdup(""));
	return (content);
}

/**
 * Handles the special case where the content is exactly $?.
 */
char	*handle_simple_exit_status(char *content, int last_exit_status)
{
	char	*result;

	if (ft_strcmp(content, "$?") == 0)
	{
		result = ft_itoa(last_exit_status);
		free(content);
		return (result);
	}
	return (NULL);
}

/**
 * Handles $? when it appears in the middle of a string.
 */
char	*handle_exit_status_with_context(char *content, char *dollar_pos,
		int last_exit_status)
{
	char	*before;
	char	*after;
	char	*exit_code;
	char	*temp;
	char	*result;

	before = ft_substr(content, 0, dollar_pos - content);
	after = ft_strdup(dollar_pos + 2);
	exit_code = ft_itoa(last_exit_status);
	temp = ft_strjoin(before, exit_code);
	result = ft_strjoin(temp, after);
	free(before);
	free(after);
	free(exit_code);
	free(temp);
	return (result);
}

/**
 * Finds the end of a variable name (alphanumeric or underscore).
 */
char	*find_variable_end(char *var_start)
{
	char	*var_end;

	var_end = var_start;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	return (var_end);
}

/**
 * Builds a new string by joining the parts before,
 * the variable value, and after the variable.
 */
char	*build_result_from_parts(char *before, char *var_value, char *var_end,
		char *var_name)
{
	char	*after;
	char	*temp;
	char	*result;

	after = ft_strdup(var_end);
	if (var_value)
		temp = ft_strjoin(before, var_value);
	else
		temp = ft_strjoin(before, "");
	result = ft_strjoin(temp, after);
	free(before);
	free(var_name);
	free(after);
	free(temp);
	return (result);
}
