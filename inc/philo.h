/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:41:35 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 17:45:07 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBRARIES */
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* COLORS */
# define BOLD_BLUE "\033[1;34m"
# define END_COLOR "\033[0m"

/* PHILOSOPHERS EVENTS */
# define DIE "died"
# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"

/* INVALID ARGUMENTS */
# define INVALID_ARGS "arguments must be positive decimal integers"
# define USAGE "usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[optional]<number_of_times_each_philosopher_must_eat>"

/* FUNCTIONS FAILURES */
# define GETTIMEOFDAY "gettimeofday failure"
# define MALLOC "malloc failure"
# define MUTEX_DESTROY "mutex destroyment failure"
# define MUTEX_INIT "mutex initialization failure"
# define MUTEX_LOCK "mutex lock failure"
# define MUTEX_UNLOCK "mutex unlock failure"
# define PRINTF "printf failure"
# define THREAD_CREATION "thread creation failure"
# define THREAD_DETACH "thread detachment failure"
# define THREAD_JOIN "thread join failure"
# define USLEEP "usleep failure"

/* ENUMS */
typedef enum e_args
{
	NUMBER_OF_PHILOSOPHERS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_MEALS
}	t_args;

typedef enum e_mutex_actions
{
	DESTROY,
	INIT,
	LOCK,
	UNLOCK
}	t_mutex_actions;

typedef enum e_thread_actions
{
	CREATE,
	DETACH,
	HEALTH,
	JOIN
}	t_thread_actions;

/* STRUCTS */
typedef struct s_philosopher
{
	sig_atomic_t	last_meal;
	int				meal_count;
	pthread_mutex_t	lock;
	pthread_mutex_t	*next_lock;
	pthread_t		thread;
	size_t			index;
	struct s_data	*data;
}	t_philosopher;

typedef struct s_data
{
	bool			death;
	int				numeric_args[5];
	pthread_mutex_t	death_lock;
	pthread_mutex_t	master_lock;
	size_t			philosopher_count;
	struct timeval	base_timestamp;
	t_philosopher	*to_free;
}	t_data;

/* FUNCTIONS */
int		ft_atoi(const char *str);
int		ft_eat(t_philosopher *philosopher, t_data *data);
int		ft_exit(char *caller_name, char *error_message, t_data *data);
int		ft_free(t_data *data);
int		ft_gettime(int *timestamp, t_data *data);
int		ft_has_anyone_died(t_data *data);
void	*ft_healthcheck(void *ptr);
char	*ft_itoa(int n);
int		ft_meal_limit_reached(t_philosopher *philosopher);
int		ft_mutex(t_mutex_actions action, pthread_mutex_t *lock, t_data *data);
void	*ft_routine(void *ptr);
int		ft_safe_usleep(t_data *data);
int		ft_sleep(t_philosopher *philosopher, t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_thread(t_thread_actions action, pthread_t *thread, void *ptr);
#endif
