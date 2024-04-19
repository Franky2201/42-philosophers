/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:57:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/19 14:53:47 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_safe_thread_create(pthread_t *thread, void *(*ft_routine)(void *), t_philosopher *philosopher)
{
	if (thread && pthread_create(thread, NULL, ft_routine, philosopher) != 0)
		ft_exit((char *)__func__, THREAD_CREATION, philosopher->to_free);
}

void	ft_safe_thread_join(pthread_t thread, t_philosopher *to_free)
{
	if (thread && pthread_join(thread, NULL) != 0)
		ft_exit((char *)__func__, THREAD_JOIN, to_free);
}
