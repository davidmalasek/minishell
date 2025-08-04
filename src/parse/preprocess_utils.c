/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 20:45:31 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/04 11:00:13 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Extracts the next token from the input,
 * updates the cursor, and handles errors.
 */
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

/**
 * Counts how many tokens are in the input string.
 */
size_t	count_tokens(const char *input, char delimiter, int *has_quotes)
{
	const char	*scan;
	size_t		token_count;
	char		*discard;

	scan = input;
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

/**
 * Fills an array with all tokens from the input.
 */
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

/**
 * Checks if a character is a delimiter or end of string.
 */
int	is_delimiter(char character, char delimiter)
{
	return (character == delimiter || character == '\0');
}

/**
 * Checks if the string at s is a shell operator (|, <, >, <<, >>).
 */
int	is_operator(const char *s)
{
	return ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>')
		|| s[0] == '<' || s[0] == '>' || s[0] == '|');
}
