/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:44 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:45 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Print the environment variables in the export list.
/// @param temp The head of the export list.
/// @return 0 on success.
int	ft_ex_print(t_env *temp)
{
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
	return (0);
}

/// @brief Adds or updates a single arg to the env and export lists.
/// @param arg The export argument to process.
/// @param export_list The export list to update.
/// @param env_list The environment list to update.
void	process_export_argument(char *arg, t_minishell *shell)
{
	char	*equal_sign;
	char	*identifier;

	equal_sign = ft_strchr(arg, '=');
	identifier = NULL;
	if (equal_sign)
		identifier = ft_strndup(arg, equal_sign - arg);
	else
		identifier = arg;
	if (!is_valid_identifier(identifier))
	{
		handle_invalid_identifier(identifier, shell, equal_sign);
		return ;
	}
	handle_valid_identifier(arg, equal_sign, shell);
	if (equal_sign)
		free(identifier);
}

/// @brief Handle the export command, adding or updating environment variables.
/// @param args The list of arguments, where each argument is a var to export.
/// @param export_list The export list to update.
/// @param env_list The environment list to update.
/// @return 0 on success, or a non-zero error code on failure.
int	ft_export(char **args, t_minishell *shell)
{
	t_env	*temp;
	int		i;

	temp = shell->export_list;
	if (!args[1])
		return (ft_ex_print(temp));
	i = 1;
	while (args[i] && !is_excluded(args[i]))
	{
		process_export_argument(args[i], shell);
		i++;
	}
	return (shell->exit_code);
}
