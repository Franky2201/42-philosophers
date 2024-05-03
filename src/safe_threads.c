/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:57:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/03 14:48:34 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_safe_thread_create(pthread_t *thread, void *(*ft_routine)(void *), t_philosopher *philosopher)
{
	if (thread && pthread_create(thread, NULL, ft_routine, philosopher) != 0)
		return (ft_exit((char *)__func__, THREAD_CREATION, philosopher->data));
	return (0);
}

static int	ft_safe_thread_join(pthread_t thread, t_data *data)
{
	void	*retval;

	retval = NULL;
	if (thread && pthread_join(thread, &retval) != 0)
		return (ft_exit((char *)__func__, THREAD_JOIN, data));
	if (retval)
		return (1);
	return (0);
}

int	ft_thread(t_thread_actions action, pthread_t *thread, void *ptr)
{
	if (action == CREATE)
		if (ft_safe_thread_create(thread, &ft_routine, (t_philosopher *)ptr))
			return (1);
	if (action == JOIN)
		if (ft_safe_thread_join(*thread, (t_data *)ptr))
			return (1);
	return (0);
}
