/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:49 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/04 15:59:50 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/// @brief Loop to simulate for the dinner and philosophers actions.
/// Will attempt to preform the actions until the end of the sim.
/// If only one Philo, it will pick one fork and end the sim.
/// @param _philo Ptr to the philo struct
/// @return Returns NULL when simullation stops
void	*dinner(void *_philo)
{
	t_philo	*philo;

	philo = (t_philo *)_philo;
	if (philo->data->philos_n == 1)
	{
		philo_speak(philo, FORK_TXT);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->stop_simu)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->mutex);
		philo_eat(philo);
		philo_sleep(philo);
		philo_speak(philo, THINK_TXT);
	}
	return (NULL);
}
