/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:53 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/04 15:59:54 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/// @brief Action for the Philosopher to drop the fork after eating.
/// Unlocks both mutex to make them available to the ther philos.
/// @param philo Ptr to the philo struct.
void	drop_forks(t_philo *philo)
{
	if (philo->philo_nbr % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

/// @brief Action for the Philosopher to pick the fork.
/// Locks both, left and right fork. The order is determined by the philo nbr.
/// If philo is even picks left then right, if not reverse order.
/// @param philo 
void	get_forks(t_philo *philo)
{
	if (philo->philo_nbr % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_speak(philo, FORK_TXT);
		pthread_mutex_lock(philo->right_fork);
		philo_speak(philo, FORK_TXT);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_speak(philo, FORK_TXT);
		pthread_mutex_lock(philo->left_fork);
		philo_speak(philo, FORK_TXT);
	}
}

/// @brief Destroy and free mutex afetr the simullation
/// @param forks The array of forks mutex.
/// @param end The index of the last fork to be destroyed.
void	cleanup_forks(pthread_mutex_t *forks, int end)
{
	int	i;

	i = 0;
	while (i <= end)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
