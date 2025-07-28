/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasklaus <tomasklaus@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 13:43:43 by davidmalase       #+#    #+#             */
/*   Updated: 2025/07/28 20:42:15 by tomasklaus       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

t_token	process_token(char *component, t_env *env, int last_exit_status)
{
	t_token	token;

	if (ft_strcmp(component, "|") == 0)
		token.type = PIPE;
	else if (ft_strcmp(component, "<") == 0)
		token.type = REDIR_IN;
	else if (ft_strcmp(component, "<<") == 0)
		token.type = HEREDOC;
	else if (ft_strcmp(component, ">") == 0)
		token.type = REDIR_OUT;
	else if (ft_strcmp(component, ">>") == 0)
		token.type = APPEND_OUT;
	else
	{
		if (component[0] == '$')
		{
			if (ft_strcmp(component, "$?") == 0)
				token.value = ft_itoa(last_exit_status);
			else
				token.value = expand_variable(component, env, last_exit_status);
		}
		else
			token.value = ft_strdup(component);
		token.type = WORD;
	}
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
