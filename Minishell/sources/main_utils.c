/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:34:18 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:34:19 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/// @brief check
/// @param line to be ckecked
/// @return 1 if line is empty or contains only spaces, 0 otherwise
int	is_empty_or_space(const char *line)
{
	if (line[0] == '\0')
		return (1);
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

/// @brief Sorts the export list in alphabetical order using bubble sort.
/// @param export_list The export list to be sorted.
void	bubble_sort(t_minishell *shell)
{
	int		swapped;
	char	*temp;
	t_env	*current;

	if (!shell->export_list)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = shell->export_list;
		while (current->next != NULL)
		{
			if (ft_strncmp(current->var, current->next->var,
					ft_strlen(current->var)) > 0)
			{
				temp = current->var;
				current->var = current->next->var;
				current->next->var = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

/// @brief Adds the "declare -x " prefix to each variable in the export list.
/// @param export_list The export list to be modified.
void	add_declare(t_minishell *shell)
{
	size_t		total_size;
	char		*new_str;
	const char	*declare_prefix;
	char		*equal;
	t_env		*exp_lst;

	declare_prefix = "declare -x ";
	exp_lst = shell->export_list;
	while (exp_lst != NULL)
	{
		total_size = ft_strlen(declare_prefix) + ft_strlen(exp_lst->var) + 3;
		new_str = (char *)malloc(total_size);
		if (!new_str)
			return ;
		ft_strlcpy(new_str, declare_prefix, total_size);
		equal = ft_strchr(exp_lst->var, '=');
		ft_strlcat(new_str, exp_lst->var, total_size - ft_strlen(equal) - 1);
		ft_strlcat(new_str, "\"", total_size);
		ft_strlcat(new_str, equal + 1, total_size);
		ft_strlcat(new_str, "\"", total_size);
		free(exp_lst->var);
		exp_lst->var = new_str;
		exp_lst = exp_lst->next;
	}
}

int	is_excluded(char *var_name)
{
	if (ft_strncmp(var_name, "SESSION_MANAGER",
			ft_strlen("SESSION_MANAGER")) == 0
		|| ft_strncmp(var_name, "QT_ACCESSIBILITY",
			ft_strlen("QT_ACCESSIBILITY")) == 0
		|| ft_strncmp(var_name, "SSH_AGENT_LAUNCHER",
			ft_strlen("SSH_AGENT_LAUNCHER")) == 0
		|| ft_strncmp(var_name, "SSH_AUTH_SOCK",
			ft_strlen("SSH_AUTH_SOCK")) == 0
		|| ft_strncmp(var_name, "XMODIFIERS", ft_strlen("XMODIFIERS")) == 0
		|| ft_strncmp(var_name, "VIRTUAL_ENV", ft_strlen("VIRTUAL_ENV")) == 0
		|| ft_strncmp(var_name, "VTE_VERSION", ft_strlen("VTE_VERSION")) == 0
		|| ft_strncmp(var_name, "WAYLAND_DISPLAY",
			ft_strlen("WAYLAND_DISPLAY")) == 0
		|| ft_strncmp(var_name, "PS1", ft_strlen("PS1")) == 0
		|| ft_strncmp(var_name, "_", ft_strlen("_")) == 0)
		return (1);
	return (0);
}
