/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:46 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:47 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Expands a token segment, handling quoted and unquoted segments.
/// @param token The input token string.
/// @param env_list The environment variable list.
/// @param i The current index in the token string.
/// @param quote The quote character (' or "), or 0 if the segment is unquoted.
/// @return The expanded segment string.
char	*expand_segment(const char *token, t_minishell *shell, size_t *i,
		char quote)
{
	char	*expanded_seg;

	if (quote)
		expanded_seg = expand_quoted_segment(token, shell, i, quote);
	else
		expanded_seg = expand_unquoted_segment(token, shell, i);
	return (expanded_seg);
}

/// @brief Handle the value of a variable by replacing it in the token.
/// @param value The value of the variable.
/// @param token The token containing the variable.
/// @return A new string with the variable value replaced, or NULL on failure.
char	*handle_variable_value(const char *value, const char *token)
{
	char	*result;
	char	*var_name;
	size_t	var_name_len;

	var_name = extract_var_name(token);
	var_name_len = ft_strlen(var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(token));
	result = malloc(ft_strlen(value) + ft_strlen(token) - var_name_len + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, value);
	ft_strcat(result, token + var_name_len + 1);
	return (result);
}

/// @brief Expand a variable in the token using the environment list.
/// @param env_list The environment list.
/// @param token The token containing the variable.
/// @return A new string with the variable expanded, or NULL on failure.
char	*expand_variable(t_minishell *shell, const char *token)
{
	char	*var_name;
	char	*value;
	char	*result;

	if (token[0] != '$' || token[1] == '\0')
	{
		if (token[0] == '$')
			return (ft_strdup("$"));
		else
			return (ft_strdup(token));
	}
	if (ft_strcmp(token, "$?") == 0)
		return (ft_itoa(shell->exit_code));
	var_name = extract_var_name(token);
	if (!var_name)
		return (NULL);
	value = get_variable_value(shell, var_name);
	free(var_name);
	if (!value)
	{
		return (ft_strdup(""));
	}
	result = handle_variable_value(value, token);
	return (result);
}

/// @brief Expands a segment and joins it to the result string.
/// @param result The current result string.
/// @param segment The segment to be expanded and joined.
/// @param env_list The environment variable list.
/// @param quote The quote character (' or "), or 0 if the segment is unquoted.
/// @return New string, the result of concat the expanded segment to the reslt.
char	*expand_and_join(char *result, char *segment, t_minishell *shell,
			char quote)
{
	char	*expanded_segment;
	char	*new_result;

	if (segment[0] == '$' && segment[1] == '?' && segment[2] == '\0')
		expanded_segment = ft_itoa(shell->exit_code);
	else if (quote == '"')
		expanded_segment = do_dq(shell, segment);
	else
		expanded_segment = expand_variable(shell, segment);
	new_result = ft_strjoin_free(result, expanded_segment);
	free(expanded_segment);
	return (new_result);
}

/// @brief Process a segment of the token, handling quotes or unquoted text.
/// @param token The token to process.
/// @param i The current index in the token.
/// @param quote The quote character (' or ") or 0 if no quote is used.
/// @return The processed segment of the token.
char	*process_expansion_segment(const char *token, size_t *i, char quote)
{
	size_t	start;

	start = *i;
	if (token[*i] == '$' && token[*i + 1] == '?')
	{
		*i += 2;
		return (ft_strdup("$?"));
	}
	while (token[*i] && token[*i] != quote)
		(*i)++;
	return (ft_substr(token, start, *i - start));
}
