/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:45:27 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/08 15:25:19 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_print_event(char *event, int *timestamp, size_t philosopher, t_data *data)
{
	if (ft_gettime(timestamp, data))
		return (1);
	if (printf("%i %zu %s\n", *timestamp, philosopher, event) < 0)
		return (ft_exit((char *)__func__, PRINTF, data));
	return (0);
}
/*
int	ft_die(t_philosopher *philosopher, t_data *data)
{
	int	time_to_die;
	int	timestamp;

	time_to_die = data->numeric_args[TIME_TO_DIE];
	if (ft_gettime(&timestamp, data))
		return (-1);
	if (timestamp / time_to_die > philosopher->meals)
		return (1);
	return (0);
}*/

int	ft_eat(t_philosopher *philosopher, t_data *data)
{
	int	elapsed;
	int	time_to_eat;
	int	timestamp;

	time_to_eat = data->numeric_args[TIME_TO_EAT];
	if (ft_mutex(LOCK, &data->master_lock, data) \
		|| ft_mutex(LOCK, &philosopher->lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data) \
		|| ft_mutex(LOCK, philosopher->next_lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data) \
		|| ft_print_event(EAT, &timestamp, philosopher->index, data) \
		|| ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	philosopher->last_meal = timestamp;
	elapsed = 0;
	while (elapsed < time_to_eat)
	{
		if (ft_safe_sleep(data) || ft_gettime(&elapsed, data))
			return (1);
		elapsed -= timestamp;
	}
	if (ft_mutex(UNLOCK, &philosopher->lock, data) \
		|| ft_mutex(UNLOCK, philosopher->next_lock, data))
		return (1);
	return (0);
}

int	ft_sleep(t_philosopher *philosopher, t_data *data)
{
	int	elapsed;
	int	time_to_sleep;
	int	timestamp;

	time_to_sleep = data->numeric_args[TIME_TO_SLEEP];
	if (ft_print_event(SLEEP, &timestamp, philosopher->index, data))
		return (1);
	elapsed = 0;
	while (elapsed < time_to_sleep)
	{
		if (ft_safe_sleep(data) || ft_gettime(&elapsed, data))
			return (1);
		elapsed -= timestamp;
	}
	if (ft_print_event(THINK, &timestamp, philosopher->index, data))
		return (1);
	return (0);
}
