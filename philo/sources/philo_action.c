/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:00:07 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/07 18:23:39 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/// @brief Handles the Philos messages with mutex permissions.
/// @param philo Ptr to the philo struct.
/// @param event Message description.
void	philo_speak(t_philo *philo, char *event)
{
	long long	elapsed_time;
	char		*color;

	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->stop_simu)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return ;
	}
	if (philo->philo_nbr % 5 == 1)
		color = RP;
	else if (philo->philo_nbr % 5 == 2)
		color = GP;
	else if (philo->philo_nbr % 5 == 3)
		color = YP;
	else if (philo->philo_nbr % 5 == 4)
		color = BP;
	else
		color = PP;
	elapsed_time = get_time() - philo->start_time;
	printf("%s%lld %d %s%s", color, elapsed_time, philo->philo_nbr, event, RST);
	pthread_mutex_unlock(&philo->data->mutex);
}

/// @brief Simulate philo sleeping pausing execution.
/// @param philo Ptr to the philo struct.
void	philo_sleep(t_philo *philo)
{
	philo_speak(philo, SLEEP_TXT);
	ft_usleep((philo->data->time_to_sleep));
}

/// @brief Simulate philo eating, locks forks, update meals and pause time.
/// @param philo Ptr to the philo struct.
void	philo_eat(t_philo *philo)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->data->mutex);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->mutex);
	philo_speak(philo, EAT_TXT);
	ft_usleep((philo->data->time_to_eat));
	drop_forks(philo);
}
