/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:49 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:50 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Extracts the Var name form token that starts with $.
/// @param token Token containing the var (Example: "$USER")
/// @return New str containing the variable name without $.
char	*extract_var_name(const char *token)
{
	return (ft_strdup(token + 1));
}

/// @brief Gets the values of an env var from the env list.
/// @param env_list  Linked list with env vars.
/// @param var_name Name of the variable to search for.
/// @return  Ptr to the value of the variable found, if not found NULL.
char	*get_variable_value(t_minishell *shell, const char *var_name)
{
	t_env	*current;
	size_t	var_len;

	if (!var_name || !*var_name)
		return (NULL);
	var_len = ft_strlen(var_name);
	current = shell->env_list;
	while (current)
	{
		if (ft_strncmp(current->var, var_name, var_len) == 0
			&& current->var[var_len] == '=')
			return (current->var + var_len + 1);
		current = current->next;
	}
	current = shell->export_list;
	while (current)
	{
		if (ft_strncmp(current->var, var_name, var_len) == 0
			&& current->var[var_len] == '=')
			return (current->var + var_len + 1);
		current = current->next;
	}
	return (NULL);
}

/// @brief Joins two strings and frees the first string.
/// @param s1 The first string, which will be freed.
/// @param s2 The second string.
/// @return New string the result of concatenating s1 and s2, NULL if error.
char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(result, s1, len1);
	ft_strlcpy(result + len1, s2, len2 + 1);
	free(s1);
	return (result);
}

/// @brief Expand a quoted segment of a token using the environment list.
/// @param token The token containing the quoted segment.
/// @param env_list The environment list.
/// @param i Pointer to the current index in the token.
/// @param quote The quote character (' or ").
/// @return A new string with the quoted segment expanded, or NULL on failure.
char	*expand_quoted_segment(const char *token, t_minishell *shell, size_t *i,
			char quote)
{
	char	*expanded_seg;
	size_t	start;
	char	*temp;

	start = *i;
	while (token[*i] && token[*i] != quote)
		(*i)++;
	expanded_seg = ft_substr(token, start, *i - start);
	if (quote == '"')
	{
		temp = expanded_seg;
		expanded_seg = do_dq(shell, expanded_seg);
		free(temp);
	}
	if (token[*i])
		(*i)++;
	return (expanded_seg);
}

/// @brief Expand the exit code from the environment list.
/// @param env_list The environment list.
/// @return A string representing the exit code, or NULL on failure.
char	*expand_exit_code(t_minishell *shell)
{
	return (ft_itoa(shell->exit_code));
}
