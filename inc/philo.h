/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:41:35 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/16 16:49:26 by gde-win          ###   ########.fr       */
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
# define MALLOC_FAIL "malloc failure"
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
	pthread_mutex_t	lock;
	pthread_mutex_t	*next_lock;
	pthread_t		philosopher;
}	t_philosopher;

#endif
