/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:24 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:25 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static size_t	skip_whitespace(const char *input, size_t i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

static size_t	copy_operator(t_segment_data *segment_data, size_t i,
	size_t len)
{
	segment_data->result[(*segment_data->count)++]
		= ft_strndup(segment_data->input + i, len);
	return (skip_whitespace(segment_data->input, i + len));
}

static size_t	process_quotes(const char *input, size_t i, char *quote)
{
	if (*quote == '\0')
		*quote = input[i];
	else if (*quote == input[i])
		*quote = '\0';
	return (i + 1);
}

static size_t	copy_word(t_segment_data *segment_data, size_t start,
	size_t end)
{
	if (end > start)
		segment_data->result[(*segment_data->count)++]
			= ft_strndup(segment_data->input + start, end - start);
	return (end);
}

/// @brief Extract a segment from the input string.
/// @param input The input string.
/// @param result The array to store the extracted segments.
/// @param count Pointer to the count of segments extracted.
/// @param i The current index in the input string.
/// @return The updated index in the input string after extraction.
size_t	extract_segment(const char *inp, char **result, size_t *count,
	size_t i)
{
	char			quote;
	size_t			start;
	t_segment_data	segment_data;

	quote = '\0';
	segment_data.input = inp;
	segment_data.result = result;
	segment_data.count = count;
	i = skip_whitespace(inp, i);
	start = i;
	while (inp[i])
	{
		if ((ft_strncmp(inp + i, ">>", 2) == 0
				|| ft_strncmp(inp + i, "<<", 2) == 0) && quote == '\0')
			return (copy_operator(&segment_data, i, 2));
		if ((inp[i] == '|' || inp[i] == '<' || inp[i] == '>') && quote == '\0')
			return (copy_operator(&segment_data, i, 1));
		if (inp[i] == '\'' || inp[i] == '"')
			i = process_quotes(inp, i, &quote);
		else if (inp[i] == ' ' && quote == '\0')
			break ;
		else
			i++;
	}
	return (copy_word(&segment_data, start, i));
}
