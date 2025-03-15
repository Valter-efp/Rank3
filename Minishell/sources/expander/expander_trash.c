/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_trash.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:58 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:59 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/* 
	These are olders functions that were used in the expander
	Kepp them just in case we need them later
*/

// int	has_quotes(const char *token)
// {
// 	if (!token)
// 		return (0);
// 	while (*token)
// 	{
// 		if (*token == '"' || *token == '\'')
// 			return (1);
// 		token++;
// 	}
// 	return (0);
// }

// /// @brief If there is an expansion inside a dq token
// /// @param token Token to be precessed
// /// @param env_list List to retriev expansion
// ///TODO maybe change this to export_list
// /// @return The expanded value if wrapped
// /* Semi-working, messed multiple variable expansion */
// char	*expand_inner_variable(const char *token, t_env *env_list)
// {
// 	char	*inner_token;
// 	char	*expanded_value;
// 	char	*result;

// 	if (token[0] == '\'' && token[strlen(token) - 1] == '\'')
// 	{
// 		inner_token = ft_strtrim(token, "\'");
// 		expanded_value = expand_variable(env_list, inner_token);
// 		free(inner_token);
// 		result = malloc(strlen(expanded_value) + 3);
// 		if (result)
// 		{
// 			sprintf(result, "'%s'", expanded_value);
// 		}
// 		free(expanded_value);
// 		return (result);
// 	}
// 	else if (token[0] == '"' && token[strlen(token) - 1] == '"')
// 	{
// 		inner_token = ft_strtrim(token, "\"");
// 		expanded_value = expand_variable(env_list, inner_token);
// 		free(inner_token);
// 		return (expanded_value);
// 	}
// 	return (NULL);
// }

/// @brief Handles the expansion of a token that may contain quoted segments.
/// @param token The token to be processed.
/// @param env_list The environment variable list.
/// @return The expanded token string.
// char	*handle_token_in_quotes(const char *token, t_env *env_list)
// {
// 	char	*result;
// 	char	*segment;
// 	size_t	i;

// 	result = NULL;
// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '\'' || token[i] == '"')
// 		{
// 			segment = process_expansion_segment(token, &i, token[i]);
// 			result = expand_and_join(result, segment, env_list, token[i - 1]);
// 			free(segment);
// 			if (token[i])
// 				i++;
// 		}
// 		else
// 		{
// 			segment = process_expansion_segment(token, &i, '\0');
// 			result = expand_and_join(result, segment, env_list, '\0');
// 			free(segment);
// 		}
// 	}
// 	return (result);
// }

/// @brief Checks if token starts with $, if so its a variable.
/// @param token Token to be checked.
/// @return 1 if starts with $ otherwise 0.
// int	starts_with_variable(const char *token)
// {
// 	return (token[0] == '$');
// }
