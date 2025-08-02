/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:43:43 by davidmalase       #+#    #+#             */
/*   Updated: 2025/08/02 14:50:11 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_variable_expansion(char *content, char *dollar_pos, t_env *env)
{
	char	*var_start;
	char	*var_end;
	char	*before;
	char	*var_name;
	char	*var_value;

	var_start = dollar_pos + 1;
	var_end = find_variable_end(var_start);
	before = ft_substr(content, 0, dollar_pos - content);
	var_name = ft_substr(var_start, 0, var_end - var_start);
	var_value = get_env_value(env, var_name);
	return (build_result_from_parts(before, var_value, var_end, var_name));
}

char	*expand_in_double_quotes(char *component, t_env *env,
		int last_exit_status)
{
	char	*content;
	char	*result;
	char	*dollar_pos;

	content = extract_quoted_content(component);
	dollar_pos = ft_strchr(content, '$');
	if (!dollar_pos)
	{
		result = ft_strdup(content);
		free(content);
		return (result);
	}
	result = handle_simple_exit_status(content, last_exit_status);
	if (result)
		return (result);
	if (dollar_pos[1] == '?')
	{
		result = handle_exit_status_with_context(content, dollar_pos,
				last_exit_status);
		free(content);
		return (result);
	}
	result = handle_variable_expansion(content, dollar_pos, env);
	free(content);
	return (result);
}

t_token	process_token(char *component, t_env *env, int last_exit_status)
{
	t_token	token;
	int		operator_type;

	operator_type = get_operator_token_type(component);
	if (operator_type != -1)
	{
		token.type = operator_type;
		token.value = NULL;
		return (token);
	}
	token.value = process_word_token(component, env, last_exit_status);
	token.type = WORD;
	return (token);
}

t_token	*tokenize(char *input, t_env *env, int last_exit_status,
		int *has_quotes)
{
	char	**input_split;
	t_token	*tokens;
	size_t	components_count;
	size_t	i;

	i = 0;
	input_split = custom_split(input, ' ', has_quotes);
	if (!input_split)
		return (NULL);
	components_count = get_array_length(input_split);
	tokens = malloc(sizeof(t_token) * (components_count + 1));
	if (!tokens)
		return (NULL);
	while (i < components_count)
	{
		tokens[i] = process_token(input_split[i], env, last_exit_status);
		free(input_split[i]);
		i++;
	}
	tokens[i].value = NULL;
	tokens[i].type = -1;
	free(input_split);
	return (tokens);
}

/* STARÉ A DLOUHÉ
char	*expand_in_double_quotes(char *component, t_env *env,
		int last_exit_status)
{
	char	*content;
	char	*result;
	int		len;
	char	*dollar_pos;
	char	*var_value;
	char	*before;
	char	*after;
	char	*exit_code;
	char	*temp;
	char	*var_start;
	char	*var_end;
	char	*var_name;

	len = ft_strlen(component);
	content = ft_substr(component, 1, len - 2);
	if (!content)
		return (ft_strdup(""));
	dollar_pos = ft_strchr(content, '$');
	if (!dollar_pos)
	{
		result = ft_strdup(content);
		free(content);
		return (result);
	}
	if (ft_strcmp(content, "$?") == 0)
	{
		result = ft_itoa(last_exit_status);
		free(content);
		return (result);
	}
	if (dollar_pos[1] == '?')
	{
		before = ft_substr(content, 0, dollar_pos - content);
		after = ft_strdup(dollar_pos + 2);
		exit_code = ft_itoa(last_exit_status);
		temp = ft_strjoin(before, exit_code);
		result = ft_strjoin(temp, after);
		free(before);
		free(after);
		free(exit_code);
		free(temp);
		free(content);
		return (result);
	}
	var_start = dollar_pos + 1;
	var_end = var_start;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	before = ft_substr(content, 0, dollar_pos - content);
	var_name = ft_substr(var_start, 0, var_end - var_start);
	var_value = get_env_value(env, var_name);
	after = ft_strdup(var_end);
	temp = ft_strjoin(before, var_value ? var_value : "");
	result = ft_strjoin(temp, after);
	free(before);
	free(var_name);
	free(after);
	free(temp);
	free(content);
	return (result);
}

t_token	process_token(char *component, t_env *env, int last_exit_status)
{
	t_token	token;
	char	**input_split;
	t_token	*tokens;
	size_t	components_count;
	size_t	i;
	char	**input_split;
	t_token	*tokens;
	size_t	components_count;
	size_t	i;
	char	**input_split;
	t_token	*tokens;
	size_t	components_count;
	size_t	i;

	if (ft_strcmp(component, "|") == 0)
		token.type = PIPE;
	else if (ft_strcmp(component, "<<") == 0)
		token.type = HEREDOC;
	else if (ft_strcmp(component, "<") == 0)
		token.type = REDIR_IN;
	else if (ft_strcmp(component, ">>") == 0)
		token.type = APPEND_OUT;
	else if (ft_strcmp(component, ">") == 0)
		token.type = REDIR_OUT;
	else
	{
		if (is_single_quoted(component))
		{
			token.value = remove_quotes(component);
		}
		else if (is_double_quoted(component))
		{
			token.value = expand_in_double_quotes(component, env,
					last_exit_status);
		}
		else if (component[0] == '$')
		{
			if (ft_strcmp(component, "$?") == 0)
				token.value = ft_itoa(last_exit_status);
			else
				token.value = expand_variable(component, env, last_exit_status);
		}
		else
		{
			token.value = remove_quotes(component);
		}
		token.type = WORD;
	}
	return (token);
}*/