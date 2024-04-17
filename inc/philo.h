/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:41:35 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/17 20:02:26 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/inc/libft.h"
# include <pthread.h>
# include <stdio.h>

# define BOLD_BLUE "\033[1;34m"
# define END_COLOR "\033[0m"

# define INVALID_ARGS "Arguments must be positive decimal integers"
# define MALLOC "malloc failure"
# define MUTEX_DESTROY "mutex destroyment failure"
# define MUTEX_INIT "mutex initialization failure"
# define MUTEX_LOCK "mutex lock failure"
# define MUTEX_UNLOCK "mutex unlock failure"
# define THREAD_CREATION "thread creation failure"
# define THREAD_JOIN "thread join failure"
# define USAGE "Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[optional]<number_of_times_each_philosopher_must_eat>"

typedef enum e_args
{
	NUMBER_OF_PHILOSOPHERS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_MEALS
}	t_args;

typedef struct s_philosopher
{
	int				i;
	pthread_mutex_t	lock;
	pthread_mutex_t	*master_lock;
	pthread_mutex_t	*next_lock;
	pthread_t		thread;
}	t_philosopher;

void	ft_safe_thread_create(pthread_t *thread, (void *)(*routine)(void *), t_philosopher *philosophers, int index);
void	ft_safe_thread_join(pthread_t *thread, t_philosophers *philosophers);
void	ft_safe_mutex_destroy(pthread_mutex_t *lock, t_philosopher *philosophers);
void	ft_safe_mutex_init(pthread_mutex_t *lock, t_philosopher *philosophers);
void	ft_safe_mutex_lock(pthread_mutex_t *lock, t_philosopher *philosophers);
void	ft_safe_mutex_unlock(pthread_mutex_t *lock, t_philosopher *philosophers);

#endif
