/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_and_exit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:59:58 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/04 15:59:59 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/// @brief Cleans mutex, and structs.
/// @param forks Ptr to the array of forks (mutex).
/// @param data Ptr to the data struct.
/// @param philo Ptr to the array of philo structs.
void	cleanup(pthread_mutex_t *forks, t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data)
		pthread_mutex_destroy(&data->mutex);
	if (philo)
		free(philo);
	if (forks && data && data->philos_n > 0)
	{
		while (i < data->philos_n)
		{
			pthread_mutex_destroy(&forks[i]);
			i++;
		}
		free(forks);
	}
}

void	ft_perror(const char *message)
{
	if (message)
	{
		write(STDERR_FILENO, "ERROR: ", 7);
		write(STDERR_FILENO, message, ft_strlen((char *)message));
		write(STDERR_FILENO, "\n", 1);
	}
}

/// @brief Deals with errors and properly exits the program.
/// @param forks Ptr to the array of forks (mutex).
/// @param args Ptr to the data struct.
/// @param philo Ptr to the array of philo structs.
/// @param error Error message to be displayed.
int	handle_error_and_exit(pthread_mutex_t *forks, t_data *args,
			t_philo *philo, char *error)
{
	cleanup(forks, args, philo);
	ft_perror(error);
	return (0);
}
