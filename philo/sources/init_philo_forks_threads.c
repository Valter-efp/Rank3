/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_forks_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:00:01 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/04 16:00:02 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/// @brief Allocates memory SAFELY!
/// A wrapper for malloc that checks for allocation failure and handles
/// errors if necessary by cleaning up and exiting.
/// @param size Memory size to be allocated.
/// @param data Ptr to the data struct to clean it.
/// @return Ptr to the allocated memory.
// void	*safe_malloc(int size, void *data)
// {
// 	void	*res;

// 	res = malloc(size);
// 	if (!res)
// 		handle_error_and_exit(res, data, NULL, MALLOC_ERR);
// 	return (res);
// }

void	*safe_malloc(int size, void *data)
{
	void	*res;

	res = malloc(size);
	if (!res)
	{
		handle_error_and_exit(res, data, NULL, MALLOC_ERR);
		return (NULL);
	}
	return (res);
}

/// @brief Initializes the PHilosophers struct.
/// @param data Ptr to the data struct.
/// @param forks Ptr to the array of forks (mutex).
/// @return Ptr to the array of initialized Philos.
// t_philo	*philos_init(t_data *data, pthread_mutex_t *forks)
// {
// 	t_philo	*philo;
// 	int		i;

// 	i = -1;
// 	philo = malloc(data->philos_n * sizeof(t_philo));
// 	if (!philo)
// 		handle_error_and_exit(forks, data, philo, MALLOC_ERR);
// 	while (++i < data->philos_n)
// 	{
// 		philo[i].philo_nbr = i + 1;
// 		philo[i].meal_count = 0;
// 		philo[i].left_fork = &forks[i];
// 		philo[i].right_fork = &forks[(i + 1) % data->philos_n];
// 		philo[i].last_meal_time = get_time();
// 		philo[i].data = data;
// 	}
// 	return (philo);
// }

t_philo	*philos_init(t_data *data, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(data->philos_n * sizeof(t_philo));
	if (!philo)
	{
		handle_error_and_exit(forks, data, philo, MALLOC_ERR);
		return (NULL);
	}
	while (++i < data->philos_n)
	{
		philo[i].philo_nbr = i + 1;
		philo[i].meal_count = 0;
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % data->philos_n];
		philo[i].last_meal_time = get_time();
		philo[i].data = data;
	}
	return (philo);
}

/// @brief Initializes mutexes for the forks.
/// If the initializaion fails uses cleanupandexit.
/// @param data Ptr to the data struct.
/// @return Ptr to the array of initialized fork mutexes.
// pthread_mutex_t	*forks_init(t_data *data)
// {
// 	pthread_mutex_t	*forks;
// 	int				i;

// 	i = 0;
// 	forks = safe_malloc(data->philos_n * sizeof(pthread_mutex_t), data);
// 	while (i < data->philos_n)
// 	{
// 		if (pthread_mutex_init(&forks[i], NULL) != 0)
// 		{
// 			cleanup_forks(forks, i);
// 			handle_error_and_exit(forks, data, NULL, MUTEX_ERR);
// 		}
// 		i++;
// 	}
// 	return (forks);
// }

pthread_mutex_t	*forks_init(t_data *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = safe_malloc(data->philos_n * sizeof(pthread_mutex_t), data);
	if (!forks)
		return (NULL);
	while (i < data->philos_n)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			cleanup_forks(forks, i);
			handle_error_and_exit(forks, data, NULL, MUTEX_ERR);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

/// @brief Initializes philosopher threads and starts the simulation.
/// @param data Ptr to the data struct.
/// @param fork Ptr to the array of forks (mutex).
/// @param philo Ptr to the array of philos sruct.
/// @return 
int	init_philo_threads(t_data *data, pthread_mutex_t *fork, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->philos_n)
	{
		philo[i].start_time = get_time();
		if (pthread_create(&philo[i].philo_id, NULL, dinner,
				(void *)&philo[i]) != 0)
		{
			handle_error_and_exit(fork, data, philo, THREAD_ERR);
			return (0);
		}
	}
	monitor_philos(philo, data);
	i = 0;
	while (i < data->philos_n)
	{
		if (pthread_join(philo[i].philo_id, NULL) != 0)
		{
			handle_error_and_exit(fork, data, philo, THREAD_JOIN_ERR);
			return (0);
		}
		i++;
	}
	return (1);
}
