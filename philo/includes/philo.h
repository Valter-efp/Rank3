/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafernan <vafernan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:57:28 by vafernan          #+#    #+#             */
/*   Updated: 2025/02/04 14:16:10 by vafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>	//mutex: init, destroy, lock, unlock
# include <sys/time.h>	//get time of the day
# include <stdio.h>		//printf
# include <stdlib.h>	//malloc, free
# include <unistd.h>	//usleep
# include <limits.h>
//# include <errno.h>		//for safe functions
//# include <memory.h> //check if used

//Color definitioins for printf, Bold for errors
# define R		"\033[1;31m"	//Bold Red
# define G		"\033[1;32m"	//Bold Green
# define Y		"\033[1;33m"	//Bold Yellow
# define B		"\033[1;34m"	//Bold Blue
# define M		"\033[1;35m"	//Bold Magenta
# define C		"\033[1;36m"	//Bold Cyan
# define W		"\033[1;37m"	//Bold white
# define RP		"\033[31m"		//Red color for Philo text
# define GP		"\033[32m"		//Green color for Philo text
# define YP		"\033[33m"		//Yellow color for Philo text
# define BP		"\033[34m"		//Blue color for Philo text
# define PP		"\033[95m"		//Pink color for Philo text
# define FULLC	"\033[38;5;136m"//Text color for philos are full
# define RST	"\033[0m"		//Reset to defaut color

# define INVALID_ARGS "At least one argument isn't valid!"
# define MUTEX_ERR "Mutex error!"
# define MALLOC_ERR "Malloc error!"
# define THREAD_ERR "Thread create error!"
# define THREAD_JOIN_ERR "Thread join error!"

# define FORK_TXT "has taken a fork\n"
# define DEATH_TXT "died\n"
# define SLEEP_TXT "is sleeping\n"
# define EAT_TXT "is eating\n"
# define THINK_TXT "is thinking\n"

typedef struct s_data
{
	pthread_mutex_t	mutex;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				times_to_eat;
	int				philos_n;
	int				stop_simu;
}	t_data;

typedef struct s_philo
{
	int				philo_nbr;
	int				meal_count;
	long long		last_meal_time;
	long			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		philo_id;
	t_data			*data;
}	t_philo;

pthread_mutex_t	*forks_init(t_data *data);
t_philo			*philos_init(t_data *data, pthread_mutex_t *forks);
int				valid_args(int ac, char **av);
int				init_args(t_data *data, char **av);
int				init_philo_threads(t_data *data, pthread_mutex_t *fork,
					t_philo *philo);
int				check_philosopher_status(t_data *data, t_philo *philo,
					int *philo_fed);
int				ft_is_alldigits(char **av);
int				ft_strlen(char *str);
int				ft_atoi(char *str);
void			get_forks(t_philo *philo);
void			drop_forks(t_philo *philo);
void			philo_speak(t_philo *philo, char *event);
void			*dinner(void *_philo);
void			cleanup(pthread_mutex_t *forks, t_data *data, t_philo *philo);
void			ft_usleep(long int time_in_ms);
void			philo_speak(t_philo *philo, char *event);
void			philo_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
void			monitor_philos(t_philo *philo, t_data *data);
void			cleanup_forks(pthread_mutex_t *forks, int end);
int				handle_error_and_exit(pthread_mutex_t *forks, t_data *args,
					t_philo *philo, char *error);
long long		get_time(void);
int				ft_atoi_check(const char *str, long long *result);

#endif