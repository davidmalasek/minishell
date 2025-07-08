/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/08 16:25:40 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @return 1 if character is a delimiter (or end of string), otherwise 0
 */
static int	is_delimiter(char character, char delimiter)
{
	return (character == delimiter || character == '\0');
}

/**
 * Copies token into buffer without quotes
 */
static void	copy_token(char *dest, const char *src, size_t length)
{
	size_t	i;

	i = 0;
	if ((src[0] == '\'' || src[0] == '"') && src[length - 1] == src[0])
	{
		++src;
		length -= 2;
	}
	while (i < length)
	{
		dest[i] = src[i];
		i++;
	}
	dest[length] = '\0';
}
/**
 * Returns token without quotes and moves the cursor.
 */
static char	*get_token(const char **cursor, char delimiter)
{
	const char	*start;
	size_t		length;
	char		quote_char;
	char		*token;

	start = *cursor;
	length = 0;
	quote_char = 0;
	while (start[length])
	{
		if (!quote_char && (start[length] == '\'' || start[length] == '"'))
			quote_char = start[length];
		else if (quote_char && start[length] == quote_char)
			quote_char = 0;
		else if (!quote_char && is_delimiter(start[length], delimiter))
			break ;
		++length;
	}
	if (quote_char)
		return (NULL);
	token = (char *)malloc(length + 1);
	if (!token)
		return (NULL);
	copy_token(token, start, length);
	*cursor += length;
	while (**cursor && is_delimiter(**cursor, delimiter))
		++(*cursor);
	return (token);
}

/**
 * Returns array of strings - escaped tokens.
 */
char	**minishell_split(const char *input, char delimiter)
{
	size_t		token_count;
	const char	*scan;
	char		*discard;
	char		**tokens;
	size_t		index;

	scan = input;
	token_count = 0;
	while (*scan)
	{
		while (*scan && is_delimiter(*scan, delimiter))
			++scan;
		if (!*scan)
			break ;
		discard = get_token(&scan, delimiter);
		if (!discard)
			return (NULL);
		free(discard);
		++token_count;
	}
	tokens = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!tokens)
		return (NULL);
	index = 0;
	while (*input && index < token_count)
	{
		while (*input && is_delimiter(*input, delimiter))
			++input;
		if (!*input)
			break ;
		tokens[index] = get_token(&input, delimiter);
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
