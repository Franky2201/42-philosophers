/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:42:04 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/18 15:33:18 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_safe_mutex_init(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_init(lock, NULL) != 0)
		ft_exit((char *)__func__, MUTEX_INIT, to_free);
}

void	ft_safe_mutex_lock(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_lock(lock) != 0)
		ft_exit((char *)__func__, MUTEX_LOCK, to_free);
}

void	ft_safe_mutex_unlock(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_unlock(lock) != 0)
		ft_exit((char *)__func__, MUTEX_UNLOCK, to_free);
}

void	ft_safe_mutex_destroy(pthread_mutex_t *lock, t_philosopher *to_free)
{
	if (lock && pthread_mutex_destroy(lock) != 0)
		ft_exit((char *)__func__, MUTEX_DESTROY, to_free);
	//memset lock 0 ?
}
