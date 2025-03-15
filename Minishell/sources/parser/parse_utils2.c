/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:27 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:28 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Simplify quotes in the input by removing consecutive quotes.
/// @param input The input string.
/// @return A new string with simplified quotes, or NULL on failure.
char	*simplify_quotes(const char *input)
{
	char	*temp;
	size_t	i;
	size_t	temp_len;

	temp = malloc(ft_strlen(input) + 1);
	i = 0;
	temp_len = 0;
	if (!temp)
		return (NULL);
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && input[i] == input[i + 1])
			i += 2;
		else
			temp[temp_len++] = input[i++];
	}
	temp[temp_len] = '\0';
	return (temp);
}

/// @brief Auxiliary function to split the command line into segments.
/// @param input The input string.
/// @param result The array to store the extracted segments.
/// @param count Pointer to the count of segments extracted.
void	split_command_line_aux(const char *input, char **result, size_t *count)
{
	char	*temp_input;
	size_t	i;

	temp_input = simplify_quotes(input);
	i = 0;
	if (!temp_input)
		return ;
	while (temp_input[i])
	{
		i = skip_spaces(temp_input, i);
		if (!temp_input[i])
			break ;
		i = extract_segment(temp_input, result, count, i);
	}
	free(temp_input);
}

/// @brief Splits the command line into tokens.
/// @param input The input string.
/// @return An array of strings containing the split tokens.
char	**split_command_line(const char *input)
{
	char	**result;
	size_t	count;

	count = 0;
	result = malloc(sizeof(char *) * (ft_strlen(input) / 2 + 2));
	if (!result)
		return (NULL);
	split_command_line_aux(input, result, &count);
	result[count] = NULL;
	return (result);
}
