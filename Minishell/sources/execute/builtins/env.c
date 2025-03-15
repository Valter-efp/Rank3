/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:36:57 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/03 15:36:58 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mini.h"

/// @brief Print the environment variables from the environment list.
/// @param env_list The environment list to print.
/// @return 0 on success.
int	ft_env(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp)
	{
		printf("%s\n", temp->var);
		temp = temp->next;
	}
	return (0);
}
