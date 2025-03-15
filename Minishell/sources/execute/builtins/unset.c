/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:39 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:40 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Remove a node from the env list that matches the given var name.
/// @param list The environment list.
/// @param var The variable name to remove.
void	remove_node(t_env **list, const char *var)
{
	t_env	*current;
	t_env	*previous;

	current = *list;
	previous = 0;
	while (current)
	{
		if (ft_strncmp(current->var, var, ft_strlen(var)) == 0)
		{
			if (previous)
			{
				previous->next = current->next;
			}
			else
				*list = current->next;
			free(current->var);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

/// @brief Unset env variables from the export and env lists.
/// @param args The list of args, where each arg is a var name to unset.
/// @param export_list The export list from which to remove the variables.
/// @param env_list The environment list from which to remove the variables.
/// @return 0 on success, or a non-zero error code on failure.
int	ft_unset(char **args, t_env **export_list, t_env **env_list)
{
	int			i;
	char		*with_prefix;

	i = 1;
	while (args[i])
	{
		with_prefix = malloc(sizeof(char) * (ft_strlen(args[i]) + 12));
		if (!with_prefix)
		{
			ft_perror("malloc\n");
			return (1);
		}
		ft_strlcpy(with_prefix, "declare -x ", ft_strlen("declare -x ") + 1);
		ft_strlcat(with_prefix, args[i], ft_strlen(with_prefix)
			+ ft_strlen(args[i]) + 1);
		remove_node(export_list, with_prefix);
		remove_node(env_list, args[i]);
		free(with_prefix);
		i++;
	}
	return (0);
}
