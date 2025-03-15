/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:47 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:48 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Helper function to compare strings until '=' or '\0'
int	compare_until_equal(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((s1[i] == '=' || s1[i] == '\0') && (s2[i] == '=' || s2[i] == '\0'))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	replace_value(t_env *current, t_env *new_node)
{
	if (current != NULL
		&& compare_until_equal(current->var, new_node->var) == 0)
	{
		free(current->var);
		current->var = ft_strdup(new_node->var);
		free(new_node->var);
		free(new_node);
		return (0);
	}
	return (1);
}

/// @brief Check if a string is a valid identifier.
/// @param str The string to check.
/// @return 1 if the string is a valid identifier, 0 otherwise.
int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	if (!isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/// @brief For invalid identifier prints error message and setting exit code.
/// @param identifier The invalid identifier.
/// @param env_list The environment list.
/// @param equal_sign Pointer to the equal sign in the identifier, if any.
void	handle_invalid_identifier(char *identifier, t_minishell *shell,
			char *equal_sign)
{
	write(STDERR_FILENO, N_V_ID, ft_strlen(N_V_ID));
	shell->exit_code = 1;
	if (equal_sign)
		free(identifier);
}

/// @brief Handle a valid identifier by adding it to the export and env list.
/// @param arg The argument containing the identifier.
/// @param equal_sign Pointer to the equal sign in the argument, if any.
/// @param export_list The export list.
/// @param env_list The environment list.
void	handle_valid_identifier(char *arg, char *equal_sign,
			t_minishell *shell)
{
	if (equal_sign)
	{
		if (key_value(shell, &arg, equal_sign) != 0)
			shell->exit_code = 1;
	}
	else
	{
		if (just_key(shell, &arg) != 0)
			shell->exit_code = 1;
	}
}
