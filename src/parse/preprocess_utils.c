/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:45:31 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/01 20:47:36 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_token(const char **cursor, char delimiter, int *has_quotes)
{
	const char	*start;
	size_t		length;
	char		quote_char;
	char		*token;

	start = *cursor;
	quote_char = 0;
	length = scan_token_length(start, delimiter, has_quotes, &quote_char);
	if (quote_char)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (NULL);
	}
	token = alloc_and_copy_token(start, length);
	if (!token)
		return (NULL);
	*cursor += length;
	while (**cursor && is_delimiter(**cursor, delimiter))
		++(*cursor);
	return (token);
}

size_t	count_tokens(const char *input, char delimiter, int *has_quotes)
{
	const char	*scan = input;
	size_t		token_count;
	char		*discard;

	token_count = 0;
	*has_quotes = 0;
	while (*scan)
	{
		while (*scan && is_delimiter(*scan, delimiter))
			++scan;
		if (!*scan)
			break ;
		discard = get_token(&scan, delimiter, has_quotes);
		if (!discard)
			return (0);
		free(discard);
		++token_count;
	}
	return (token_count);
}

char	**fill_tokens(const char *input, char delimiter, int *has_quotes,
		size_t token_count)
{
	char	**tokens;
	size_t	index;

	index = 0;
	tokens = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	while (*input && index < token_count)
	{
		while (*input && is_delimiter(*input, delimiter))
			++input;
		if (!*input)
			break ;
		tokens[index] = get_token(&input, delimiter, has_quotes);
		if (!tokens[index])
		{
			while (index > 0)
				free(tokens[--index]);
			free(tokens);
			return (NULL);
		}
		++index;
	}
	tokens[index] = NULL;
	return (tokens);
}
