/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:00:09 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/07 18:23:47 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//check if philos are full or dead

/// @brief Checks if philos are full or dead.
/// @param data  Ptr to the data struct.
/// @param philo Ptr to the philo struct.
/// @param philo_full Count the number of philos that are full.
/// @return 1 if some has died.
int	check_philosopher_status(t_data *data, t_philo *philo, int *philo_fed)
{
	long long	current_time;

	current_time = get_time();
	if (current_time - philo->last_meal_time > data->time_to_die)
	{
		pthread_mutex_unlock(&data->mutex);
		philo_speak(philo, DEATH_TXT);
		pthread_mutex_lock(&data->mutex);
		data->stop_simu = 1;
		return (1);
	}
	if (philo->meal_count >= data->times_to_eat && data->times_to_eat != -1)
	{
		(*philo_fed)++;
	}
	return (0);
}

/// @brief Auxiliary function to monitor philosophers' status.
/// @param philo Ptr to the philo struct.
/// @param data Ptr to the data struct.
/// @param philo_fed Pointer to the count of philosophers who have eaten.
/// @return 1 if a philosopher has died or all philosophers are full, or 0.
// int	mon_philos_aux(t_philo *philo, t_data *data, int *philo_fed)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philos_n)
// 	{
// 		if (check_philosopher_status(data, &philo[i], philo_fed) == 1)
// 			return (1);
// 		i++;
// 	}
// 	if (*philo_fed == data->philos_n)
// 	{
// 		data->stop_simu = 1;
// 		printf(FULLC"All Philosophers are full, they ate so much!\n"RST);
// 		return (1);
// 	}
// 	return (0);
// }

/// @brief Monitor the status of all philosophers and stop the sim if needed
/// @param philo Array of philosopher structures
/// @param data Shared data structure containing simulation parameters
/// @param philo_fed Ptr to an int tracking the number of philos have eaten
/// @return 1 if the simulation should stop, 0 otherwise
int	mon_philos_aux(t_philo *philo, t_data *data, int *philo_fed)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	while (i < data->philos_n)
	{
		if (check_philosopher_status(data, &philo[i], philo_fed) == 1)
			return (1);
		if (data->times_to_eat > 0 && philo[i].meal_count >= data->times_to_eat)
			full_philos++;
		i++;
	}
	if (data->times_to_eat > 0 && full_philos == data->philos_n)
	{
		data->stop_simu = 1;
		printf(FULLC "All Philosophers are full, they ate so much!\n" RST);
		return (1);
	}
	return (0);
}

/// @brief Monitors if philos are dead or full and ends the simulation.
/// @param philo Ptr to the philo struct.
/// @param data Ptr to the data struct.
void	monitor_philos(t_philo *philo, t_data *data)
{
	int	philo_fed;

	philo_fed = 0;
	while (1)
	{
		pthread_mutex_lock(&data->mutex);
		if (mon_philos_aux(philo, data, &philo_fed) == 1)
		{
			pthread_mutex_unlock(&data->mutex);
			return ;
		}
		pthread_mutex_unlock(&data->mutex);
		usleep(1000);
	}
}

/// @brief Beginnign og the program.
/// @param argc Argument count.
/// @param argv Argument values.
/// @return Exit_Failure or Success.
int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*fork;

	if ((valid_args(argc, argv) == 0) || (init_args(&data, argv) == 0))
	{
		handle_error_and_exit(NULL, NULL, NULL, INVALID_ARGS);
		return (EXIT_FAILURE);
	}
	fork = forks_init(&data);
	if (!fork)
		return (EXIT_FAILURE);
	philo = philos_init(&data, fork);
	if (!philo)
		return (EXIT_FAILURE);
	if (init_philo_threads(&data, fork, philo) == 0)
		return (EXIT_FAILURE);
	cleanup(fork, &data, philo);
	return (EXIT_SUCCESS);
}
