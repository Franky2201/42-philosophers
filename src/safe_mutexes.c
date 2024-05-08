/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:42:04 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/08 18:58:29 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_safe_mutex_init(pthread_mutex_t *lock, t_data *data)
{
	if (lock && pthread_mutex_init(lock, NULL) != 0)
		return (ft_exit((char *)__func__, MUTEX_INIT, data));
	return (0);
}

static int	ft_safe_mutex_lock(pthread_mutex_t *lock, t_data *data)
{
	if (lock && pthread_mutex_lock(lock) != 0)
		return (ft_exit((char *)__func__, MUTEX_LOCK, data));
	return (0);
}

static int	ft_safe_mutex_unlock(pthread_mutex_t *lock, t_data *data)
{
	if (lock && pthread_mutex_unlock(lock) != 0)
		return (ft_exit((char *)__func__, MUTEX_UNLOCK, data));
	return (0);
}

static int	ft_safe_mutex_destroy(pthread_mutex_t *lock, t_data *data)
{
	if (lock && pthread_mutex_destroy(lock) != 0)
		return (ft_exit((char *)__func__, MUTEX_DESTROY, data));
	memset(lock, 0, sizeof(pthread_mutex_t));
	return (0);
}

int	ft_mutex(t_mutex_actions action, pthread_mutex_t *lock, t_data *data)
{
	if (action == INIT)
		if (ft_safe_mutex_init(lock, data))
			return (1);
	if (action == LOCK)
		if (ft_safe_mutex_lock(lock, data))
			return (1);
	if (action == UNLOCK)
		if (ft_safe_mutex_unlock(lock, data))
			return (1);
	if (action == DESTROY)
		if (ft_safe_mutex_destroy(lock, data))
			return (1);
	return (0);
}
