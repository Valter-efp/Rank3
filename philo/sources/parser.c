/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:00:04 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/04 16:00:05 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 
	time_to_die = ft_atoi(argv[2]) is passed by the user in milliseconds, and
	I use gettime() to compare it, wich is also in milliseconds.
	time_to_eat and time_to_think are also passed in milliseconds, but I
	use them with Usleep wich is microseconds, so I need to multiply
*/

/// @brief Checks and converts a string argument to an integer.
/// @param str The string to be converted.
/// @param result Pointer to store the converted integer.
/// @return 1 if the conversion is success and within int range, or 0.
int	check_and_convert_arg(const char *str, long long *result)
{
	long long	temp;

	if (!ft_atoi_check(str, &temp) || temp > INT_MAX || temp < 1)
		return (0);
	*result = temp;
	return (1);
}

int	init_args_aux(t_data *data, char **argv)
{
	long long	temp;

	if (!check_and_convert_arg(argv[1], &temp))
		return (0);
	data->philos_n = (int)temp;
	if (!check_and_convert_arg(argv[2], &temp))
		return (0);
	data->time_to_die = temp;
	if (!check_and_convert_arg(argv[3], &temp))
		return (0);
	data->time_to_eat = temp;
	if (!check_and_convert_arg(argv[4], &temp))
		return (0);
	data->time_to_sleep = temp;
	data->times_to_eat = -1;
	if (argv[5])
	{
		if (!check_and_convert_arg(argv[5], &temp))
			return (0);
		data->times_to_eat = (int)temp;
	}
	return (1);
}

/// @brief Initializes the t_data structure with the provided arguments.
/// @param data Pointer to the t_data structure.
/// @param argv Array of argument strings.
/// @return 1 on success, 0 on failure.
int	init_args(t_data *data, char **argv)
{
	if (!init_args_aux(data, argv))
		return (0);
	if (data->philos_n == 0 || data->times_to_eat == 0)
		return (0);
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		return (0);
	data->stop_simu = 0;
	return (1);
}

/// @brief Validates the argvs passed.
/// @param ac Number of arguments.
/// @param argv Array of the argvs.
/// @return 1 on success, 0 on fail
int	valid_args(int ac, char **argv)
{
	if (!(ac == 5 || ac == 6) || (ft_is_alldigits(argv) == 0))
		return (0);
	return (1);
}
