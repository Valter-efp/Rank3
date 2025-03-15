/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:49 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:50 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Create a new export node with the given key and value.
/// @param key The key to create the export node with.
/// @param value The value to create the export node with.
/// @return A pointer to the new export node, or NULL on failure.
static t_env	*create_export_node(const char *key, const char *value)
{
	t_env	*new_export_node;

	new_export_node = malloc(sizeof(t_env));
	if (!new_export_node)
		return (NULL);
	new_export_node->var = malloc(ft_strlen(key) + ft_strlen(value) + 15);
	if (!new_export_node->var)
	{
		free(new_export_node);
		return (NULL);
	}
	ft_strlcpy(new_export_node->var, "declare -x ", 15);
	ft_strlcat(new_export_node->var, key, ft_strlen(new_export_node->var)
		+ ft_strlen(key) + 1);
	ft_strlcat(new_export_node->var, "=\"", ft_strlen(new_export_node->var)
		+ 3);
	ft_strlcat(new_export_node->var, value, ft_strlen(new_export_node->var)
		+ ft_strlen(value) + 1);
	ft_strlcat(new_export_node->var, "\"", ft_strlen(new_export_node->var)
		+ 2);
	new_export_node->next = NULL;
	return (new_export_node);
}

/// @brief Create a new environment node with the given key and value.
/// @param key The key to create the environment node with.
/// @param value The value to create the environment node with.
/// @return A pointer to the new environment node, or NULL on failure.
static t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new_env_node;

	new_env_node = malloc(sizeof(t_env));
	if (!new_env_node)
		return (NULL);
	new_env_node->var = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!new_env_node->var)
	{
		free(new_env_node);
		return (NULL);
	}
	ft_strlcpy(new_env_node->var, key, ft_strlen(key) + 1);
	ft_strlcat(new_env_node->var, "=", ft_strlen(new_env_node->var) + 2);
	ft_strlcat(new_env_node->var, value, ft_strlen(new_env_node->var)
		+ ft_strlen(value) + 1);
	new_env_node->next = NULL;
	return (new_env_node);
}

/// @brief Add a new environment node to the environment list.
/// @param env_list The head of the environment list.
/// @param new_env_node The new environment node to add to the list.
/// @return 0 on success.
static int	add_env_node(t_minishell *shell, t_env *new_env_node)
{
	t_env	*current;

	if (shell->env_list)
	{
		current = shell->env_list;
		while (current->next)
			current = current->next;
		current->next = new_env_node;
	}
	else
		shell->env_list = new_env_node;
	return (0);
}

/// @brief Allocate memory for the key and value from the argument.
/// @param key Pointer to store the allocated key.
/// @param value Pointer to store the allocated value.
/// @param args The arguments containing the key and value.
/// @param equal_sign Pointer to the equal sign in the argument.
/// @return 0 on success, -1 on failure.
static int	allocate_key_value(char **key, char **value, char **args,
	char *equal_sign)
{
	*key = ft_strndup(args[0], equal_sign - args[0]);
	if (!*key)
		return (-1);
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
	{
		free(*key);
		return (-1);
	}
	return (0);
}

/// @brief Add a key-value pair to the export and environment lists.
/// @param export_list The export list.
/// @param env_list The environment list.
/// @param args The arguments containing the key-value pair.
/// @param equal_sign Pointer to the equal sign in the argument.
/// @return 0 on success, -1 on failure.
int	key_value(t_minishell *shell, char **args, char *equal_sign)
{
	char	*key;
	char	*value;
	t_env	*new_export_node;
	t_env	*new_env_node;

	if (allocate_key_value(&key, &value, args, equal_sign) == -1)
		return (-1);
	new_export_node = create_export_node(key, value);
	new_env_node = create_env_node(key, value);
	if (!new_export_node || !new_env_node)
	{
		free(key);
		free(value);
		free(new_export_node);
		free(new_env_node);
		return (-1);
	}
	add_to_sorted_list(&(shell->export_list), new_export_node);
	add_env_node(shell, new_env_node);
	free(key);
	free(value);
	return (0);
}
