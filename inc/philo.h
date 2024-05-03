/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:41:35 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/03 18:04:55 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBRARIES */
# include "../libft/inc/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

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
# define THREAD_CREATION "thread creation failure"
# define THREAD_JOIN "thread join failure"

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
	JOIN
}	t_thread_actions;

/* STRUCTS */
typedef struct s_philosopher
{
	pthread_mutex_t	lock;
	pthread_mutex_t	*next_lock;
	pthread_t		thread;
	size_t			index;
	struct s_data	*data;
}	t_philosopher;

typedef struct s_data
{
	int				numeric_args[5];
	pthread_mutex_t	master_lock;
	size_t			philosopher_count;
	struct timeval	base_timestamp;
	t_philosopher	*to_free;
}	t_data;

/* FUNCTIONS */
int		ft_exit(char *caller_name, char *error_message, t_data *data);
int		ft_free(t_data *data);
int		ft_mutex(t_mutex_actions action, pthread_mutex_t *lock, t_data *data);
void	*ft_routine(void *ptr);
int		ft_thread(t_thread_actions action, pthread_t *thread, void *ptr);
#endif
