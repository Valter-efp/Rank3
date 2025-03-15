/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:00:15 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/05 16:53:21 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/// @brief Retruns the len of provided str.
/// @param str Str to calculate the len.
/// @return Len of the str.
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/// @brief Convert a str to an int. 
/// @param str Str to be converted.
/// @return The converted str.
// int	ft_atoi(char *str)
// {
// 	int				sign;
// 	int				i;
// 	unsigned int	res;

// 	res = 0;
// 	sign = 1;
// 	i = 0;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
// 			||str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
// 		i++;
// 	if (str[i] == '-')
// 		sign *= -1;
// 	if (str[i] == '+' || str[i] == '-')
// 		i++;
// 	while ((str[i] - '0' >= 0) && (str[i] - '0' <= 9))
// 	{
// 		res = (res * 10) + (str[i] - '0');
// 		i++;
// 	}
// 	return ((int)res * sign);
// }

/// @brief Converts a string to a long long integer with overflow checking.
/// @param str The string to be converted.
/// @param result Pointer to store the converted long long integer.
/// @return 1 if the conversion is successful and within int, or 0.
int	ft_atoi_check(const char *str, long long *result)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		num = num * 10 + (*str - '0');
		if ((sign == 1 && num > INT_MAX) || (sign == -1 && - num < INT_MIN))
			return (0);
		str++ ;
	}
	*result = num * sign;
	return (1);
}

/// @brief Checks that all argments are digits.
/// @param argv Array of arguments.
/// @return  1 if all are digit, else 0.
int	ft_is_alldigits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

//If I use this, they die a lot!

/// @brief More accurate sleep.
/// Recieves the ms time to sleep, and adds busy waiting for 0,1ms
/// @param time_in_ms  Sleep time.
void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(100);
}

/* Returns the time in milliseconds */

/// @brief Gets the current time in milliseconds.
/// @return Current time in milliseconds.
long long	get_time(void)
{
	struct timeval	now;
	long long		time;

	gettimeofday(&now, NULL);
	time = (now.tv_sec * 1e3) + (now.tv_usec / 1e3);
	return (time);
}
