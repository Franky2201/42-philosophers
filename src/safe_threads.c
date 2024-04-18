/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:57:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/18 15:26:55 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_safe_thread_create(pthread_t *thread, (void *)(*routine)(void *), t_philosopher *philosopher)
{
	if (thread && pthread_create(thread, NULL, &ft_routine, philosopher) != 0)
		ft_exit((char *)__func__, THREAD_CREATION, philosopher);
}

void	ft_safe_thread_join(pthread_t *thread, t_philosophers *philosophers)
{
	if (thread && pthread_join(thread) != 0)
		ft_exit((char *)__func__, THREAD_JOIN, philosophers);
}
