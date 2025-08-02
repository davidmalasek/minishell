/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 11:57:02 by dmalasek          #+#    #+#             */
/*   Updated: 2025/08/02 11:45:24 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	copy_token(char *dest, const char *src, size_t length)
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

size_t	quoted_token_length(const char *start, char delimiter, int *has_quotes,
		char *quote_char_out)
{
	size_t	length;
	char	quote_char;

	length = 0;
	quote_char = 0;
	while (start[length])
	{
		if (!quote_char && (start[length] == '\'' || start[length] == '"'))
		{
			quote_char = start[length];
			*has_quotes = 1;
		}
		else if (quote_char && start[length] == quote_char)
			quote_char = 0;
		else if (!quote_char && (is_delimiter(start[length], delimiter)
				|| is_operator(&start[length])))
			break ;
		++length;
	}
	*quote_char_out = quote_char;
	return (length);
}

size_t	scan_token_length(const char *start, char delimiter, int *has_quotes,
		char *quote_char_out)
{
	if (is_operator(start))
		return (operator_token_length(start, quote_char_out));
	return (quoted_token_length(start, delimiter, has_quotes, quote_char_out));
}

char	*alloc_and_copy_token(const char *start, size_t length)
{
	char	*token;

	token = (char *)malloc(length + 1);
	if (!token)
		return (NULL);
	ft_strlcpy(token, start, length + 1);
	return (token);
}

char	**custom_split(const char *input, char delimiter, int *has_quotes)
{
	size_t	token_count;
	char	**tokens;

	token_count = count_tokens(input, delimiter, has_quotes);
	if (token_count == 0)
		return (NULL);
	tokens = fill_tokens(input, delimiter, has_quotes, token_count);
	return (tokens);
}
