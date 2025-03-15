/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:29 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:30 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*handle_token_with_expansions(const char *token, t_minishell *shell)
{
	char	*result;
	char	*expanded_seg;
	size_t	i;

	if (check_unclosed_quotes(token))
		return (NULL);
	if ((ft_strcmp(token, "''") == 0) || (ft_strcmp(token, "\"\"") == 0))
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token[i])
	{
		expanded_seg = process_token(token, shell, &i);
		if (!expanded_seg)
		{
			free(result);
			return (NULL);
		}
		result = join_expanded_segment(result, expanded_seg);
		free(expanded_seg);
	}
	return (check_empty_result(result, token));
}

/// @brief Joins an expanded segment to the result string.
/// @param result The current result string.
/// @param expanded_seg The expanded segment to be joined.
/// @return The new result string.
char	*join_expanded_segment(char *result, char *segment)
{
	char	*new_result;

	new_result = ft_strjoin(result, segment);
	free(result);
	return (new_result);
}

/// @brief Processes a single input token and adds it to the token list.
/// @param args The token arguments structure.
/// @param input The input token.
/// @return 1 if the token was added successfully, otherwise 0.
int	process_single_input(t_token_args *args, char *input, t_minishell *shell)
{
	add_token_from_input(args, input, shell);
	return (*(args->head) != NULL);
}

/// @brief If the result string is empty returns the original token.
/// @param result The result string.
/// @param token The original token.
/// @return The original token if the result is empty, otherwise the res strg.
char	*check_empty_result(char *result, const char *token)
{
	if (*result == '\0')
	{
		if (token[0] == '$' && token[1] != '\0')
			return (result);
		free(result);
		return (ft_strdup(token));
	}
	return (result);
}

/// @brief Frees the memory allocated for the split input.
/// @param split_input The array of strings to be freed.
void	free_split_input(char **split_input)
{
	int	i;

	i = 0;
	while (split_input[i] != NULL)
	{
		free(split_input[i]);
		i++;
	}
	free(split_input);
}
