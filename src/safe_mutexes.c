/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:42:04 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/19 17:21:08 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_safe_mutex_init(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_init(lock, NULL) != 0)
		return (ft_exit((char *)__func__, MUTEX_INIT, to_free));
	return (0);
}

static int	ft_safe_mutex_lock(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_lock(lock) != 0)
		return (ft_exit((char *)__func__, MUTEX_LOCK, to_free));
	return (0);
}

static int	ft_safe_mutex_unlock(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_unlock(lock) != 0)
		return (ft_exit((char *)__func__, MUTEX_UNLOCK, to_free));
	return (0);
}

static int	ft_safe_mutex_destroy(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_destroy(lock) != 0)
		return (ft_exit((char *)__func__, MUTEX_DESTROY, to_free));
	memset(lock, 0, sizeof(pthread_mutex_t));
	return (0);
}

int	ft_mutex(t_mutex_actions action, pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (action == DESTROY)
		if (ft_safe_mutex_destroy(lock, to_free))
			return (1);
	if (action == INIT)
		if (ft_safe_mutex_init(lock, to_free))
			return (1);
	if (action == LOCK)
		if (ft_safe_mutex_lock(lock, to_free))
			return (1);
	if (action == UNLOCK)
		if (ft_safe_mutex_unlock(lock, to_free))
			return (1);
	return (0);
}
