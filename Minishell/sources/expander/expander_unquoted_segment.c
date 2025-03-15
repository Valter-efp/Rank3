/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_unquoted_segment.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:52 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:53 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

static char	*handle_dollar_aux(t_minishell *shell, char *segment,
			size_t var_start, size_t *j)
{
	char	*temp;
	char	*expanded_var;

	temp = ft_substr(segment, var_start + 1, *j - var_start - 1);
	expanded_var = get_variable_value(shell, temp);
	if (!expanded_var)
		expanded_var = "";
	free(temp);
	return (expanded_var);
}

// char	*handle_dollar(char *segment, t_minishell *shell, char *expanded_seg,
// 			size_t *j)
// {
// 	char	*temp;
// 	size_t	var_start;

// 	(*j)++;
// 	if (segment[*j] == '?')
// 	{
// 		temp = expand_exit_code(shell);
// 		if (temp)
// 		{
// 			expanded_seg = join_expanded_segment(expanded_seg, temp);
// 			free(temp);
// 		}
// 		(*j)++;
// 		return (expanded_seg);
// 	}
// 	var_start = *j - 1;
// 	while (segment[*j] && (ft_isalnum(segment[*j]) || segment[*j] == '_'))
// 		(*j)++;
// 	temp = handle_dollar_aux(shell, segment, var_start, j);
// 	expanded_seg = join_expanded_segment(expanded_seg, temp);
// 	return (expanded_seg);
// }

char	*handle_dollar(char *segment, t_minishell *shell, char *expanded_seg,
			size_t *j)
{
	char	*temp;
	size_t	var_start;

	(*j)++;
	if (segment[*j] == '?')
	{
		temp = expand_exit_code(shell);
		if (temp)
		{
			expanded_seg = join_expanded_segment(expanded_seg, temp);
			free(temp);
		}
		(*j)++;
		return (expanded_seg);
	}
	var_start = *j - 1;
	if (!ft_isalpha(segment[*j]) && segment[*j] != '_')
		return (append_char_to_segment(segment, expanded_seg, j));
	while (segment[*j] && (ft_isalnum(segment[*j]) || segment[*j] == '_'))
		(*j)++;
	temp = handle_dollar_aux(shell, segment, var_start, j);
	expanded_seg = join_expanded_segment(expanded_seg, temp);
	return (expanded_seg);
}

/// @brief Append a character from the segment to the expanded segment.
/// @param segment The original segment.
/// @param expanded_seg The expanded segment.
/// @param j Pointer to the current index in the segment.
/// @return The expanded segment with the character appended.
char	*append_char_to_segment(char *segment, char *expanded_seg, size_t *j)
{
	char	*temp;

	temp = ft_substr(segment, *j, 1);
	expanded_seg = join_expanded_segment(expanded_seg, temp);
	free(temp);
	(*j)++;
	return (expanded_seg);
}

char	*expand_dollar_segment(char *segment, t_minishell *shell,
	char *expanded_seg)
{
	size_t	j;
	char	*preprocessed_segment;

	j = 0;
	preprocessed_segment = preprocess_segment(segment);
	if (!preprocessed_segment)
		return (NULL);
	while (preprocessed_segment[j])
	{
		if (preprocessed_segment[j] == '$')
			expanded_seg = handle_dollar(preprocessed_segment, shell,
					expanded_seg, &j);
		else
			expanded_seg = append_char_to_segment(preprocessed_segment,
					expanded_seg, &j);
	}
	free(preprocessed_segment);
	return (expanded_seg);
}

/// @brief Expand an unquoted segment of a token using the environment list.
/// @param token The token containing the unquoted segment.
/// @param env_list The environment list.
/// @param i Pointer to the current index in the token.
/// @return A new string with the unquoted segment expanded, or NULL on failure.
char	*expand_unquoted_segment(const char *token, t_minishell *shell,
			size_t *i)
{
	size_t	start;
	char	*segment;
	char	*expanded_seg;

	start = *i;
	while (token[*i] && token[*i] != ' ' && token[*i] != '\''
		&& token[*i] != '"')
		(*i)++;
	segment = ft_substr(token, start, *i - start);
	expanded_seg = ft_strdup("");
	expanded_seg = expand_dollar_segment(segment, shell, expanded_seg);
	free(segment);
	return (expanded_seg);
}
