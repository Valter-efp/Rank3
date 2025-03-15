/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:52 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:53 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Add a new node to a sorted environment list.
/// @param list The head of the environment list.
/// @param new_node The new node to add to the list.
void	add_to_sorted_list(t_env **list, t_env *new_node)
{
	t_env	*current;

	if (*list == NULL || ft_strncmp(new_node->var, (*list)->var,
			ft_strlen(new_node->var)) < 0)
	{
		new_node->next = *list;
		*list = new_node;
	}
	else
	{
		current = *list;
		while (current->next != NULL && replace_value(current, new_node))
			current = current->next;
		if (current->next == NULL && replace_value(current, new_node))
		{
			new_node->next = current->next;
			current->next = new_node;
		}
	}
}

/// @brief Create a new export node with the given argument.
/// @param arg The argument to create the export node with.
/// @return A pointer to the new export node, or NULL on failure.
static t_env	*create_export_node(const char *arg)
{
	t_env	*new_export_node;

	new_export_node = malloc(sizeof(t_env));
	if (!new_export_node)
		return (NULL);
	new_export_node->var = malloc(ft_strlen(arg) + 15);
	if (!new_export_node->var)
	{
		free(new_export_node);
		return (NULL);
	}
	ft_strlcpy(new_export_node->var, "declare -x ", 15);
	ft_strlcat(new_export_node->var, arg, ft_strlen(arg) + 15);
	new_export_node->next = NULL;
	return (new_export_node);
}

/// @brief Add a key to the export and environment lists.
/// @param export_list The export list.
/// @param env_list The environment list.
/// @param args The arguments containing the key to add.
/// @return 0 on success, -1 on failure.
int	just_key(t_minishell *shell, char **args)
{
	t_env	*new_export_node;

	new_export_node = create_export_node(args[0]);
	if (!new_export_node)
	{
		free(new_export_node);
		return (-1);
	}
	add_to_sorted_list(&(shell->export_list), new_export_node);
	return (0);
}

/// @brief Clean the value by removing unwanted characters.
/// @param value The value to clean.
/// @return The cleaned value.
char	*clean_value(char *value)
{
	char	*cleaned;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cleaned = malloc(ft_strlen(value) + 1);
	if (!cleaned)
		return (0);
	while (value[i])
	{
		if (value[i] != '"' && value[i] != '\'' && value[i] != '\\')
			cleaned[j++] = value[i];
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}
