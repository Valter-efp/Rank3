/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:35:37 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:35:38 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

/// @brief Initialize the environment list with the given environment variables.
/// @param envp The environment variables array.
/// @return A pointer to the head of the environment list.
t_env	*initialize_env(char **envp, t_minishell *shell)
{
	t_env		*env_list;

	env_list = cpy_env_to_list(envp);
	if (!env_list)
	{
		printf("Failed to copy Env Variables\n");
		exit(1);
	}
	shell->exit_code = 0;
	return (env_list);
}

/// @brief Copies the env var from the array to the list.
/// @param envp Ptr to the array of string that cointains env vars.
/// @return Ptr to the head of the list.
t_env	*cpy_env_to_list(char **envp)
{
	t_env	*env_list;
	t_env	*current;
	t_env	*new_node;
	int		i;

	env_list = NULL;
	current = NULL;
	new_node = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->var = ft_strdup(envp[i]);
		new_node->next = NULL;
		if (env_list == NULL)
			env_list = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (env_list);
}

/// @brief Frees the env list.
/// @param head Ptr to the head of the env list.
void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->var)
			free(current->var);
		free(current);
		current = next_node;
	}
}

/// @brief Convert the environment list to an array of strings.
/// @param env_list The environment list.
/// @return An array of strings representing the environment variables or NULL.
char	**env_list_to_array(t_env *env_list)
{
	t_env	*temp;
	size_t	count;
	char	**env_array;
	size_t	i;

	temp = env_list;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
	temp = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i] = ft_strdup(temp->var);
		temp = temp->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}
