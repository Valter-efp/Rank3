/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:42 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:43 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Check if there are any unclosed quotes in the token.
/// @param token The token to check.
/// @return 1 if there are unclosed quotes, 0 otherwise.
int	check_unclosed_quotes(const char *token)
{
	int		i;
	bool	sq;
	bool	dq;

	i = 0;
	sq = false;
	dq = false;
	while (token[i])
	{
		if (token[i] == '\'' && !dq)
			sq = !sq;
		else if (token[i] == '"' && !sq)
			dq = !dq;
		i++;
	}
	return (sq || dq);
}

/// @brief Extract variable segment from the str starting at the given position.
/// The variable segment is a string starting with a $ and containing only
///	alphanumeric characters and underscores.
/// @param str The string to extract from.
/// @param i Pointer to the current index in the string.
/// @return The extracted variable segment.
char	*extract_variable_segment(const char *str, size_t *i)
{
	size_t	start;

	start = (*i)++;
	if (str[*i] == '?' || isspace(str[*i]) || str[*i] == '\0')
	{
		if (str[*i] == '?')
			(*i)++;
		return (ft_substr(str, start, *i - start));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

/// @brief Extract a simple segment from the str starting at the given index.
/// Simple segment is a segment that does not contain any variables.
/// @param str The string to extract from.
/// @param i Pointer to the current index in the string.
/// @return The extracted simple segment.
char	*extract_simple_segment(const char *str, size_t *i)
{
	size_t	start;
	char	*segment;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	segment = ft_substr(str, start, *i - start);
	return (segment);
}

char	*do_dq(t_minishell *shell, const char *token)
{
	char	*trimmed;
	char	*result;
	char	*segment;
	char	*expanded_var;
	size_t	i;

	trimmed = ft_strtrim(token, "\"");
	result = ft_strdup("");
	i = 0;
	while (trimmed[i])
	{
		segment = extract_simple_segment(trimmed, &i);
		result = join_expanded_segment(result, segment);
		free(segment);
		if (trimmed[i] == '$')
		{
			segment = extract_variable_segment(trimmed, &i);
			expanded_var = expand_variable(shell, segment);
			result = join_expanded_segment(result, expanded_var);
			free(segment);
			free(expanded_var);
		}
	}
	free(trimmed);
	return (result);
}
