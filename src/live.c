/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:45:27 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 19:37:43 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_has_passed(int elapsed, size_t i, t_data *data)
{
	int		time_to_die;

	time_to_die = data->numeric_args[TIME_TO_DIE];
	if (elapsed >= time_to_die)
	{
		if (ft_mutex(LOCK, &data->death_lock, data))
			return (1);
		if (ft_gettime(&elapsed, data))
			return (1);
		if (printf("%i\t%zu\t%s\n", elapsed, i + 1, DIE) < 0)
			return (ft_exit((char *)__func__, PRINTF, data));
		data->death = true;
		if (ft_mutex(UNLOCK, &data->death_lock, data))
			return (1);
		return (0);
	}
	return (2);
}

int	ft_die(t_philosopher *philosophers, t_data *data, bool *flag)
{
	int		elapsed;
	int		result;
	size_t	i;

	i = 0;
	while (i < data->philosopher_count)
	{
		if (!ft_meal_limit_reached(&philosophers[i]))
		{
			*flag = false;
			if (ft_gettime(&elapsed, data))
				return (1);
			if (ft_mutex(LOCK, &data->master_lock, data))
				return (1);
			elapsed -= philosophers[i].last_meal;
			if (ft_mutex(UNLOCK, &data->master_lock, data))
				return (1);
			result = ft_has_passed(elapsed, i, data);
			if (result != 2)
				return (result);
		}
		i++;
	}
	return (0);
}

static int	ft_has_not_finished_eating(int timestamp, t_data *data)
{
	int	elapsed;
	int	time_to_eat;

	time_to_eat = data->numeric_args[TIME_TO_EAT];
	elapsed = 0;
	while (elapsed < time_to_eat)
	{
		if (ft_safe_usleep(data) || ft_gettime(&elapsed, data))
			return (1);
		elapsed -= timestamp;
	}
	return (0);
}

int	ft_eat(t_philosopher *philosopher, t_data *data)
{
	int	timestamp;

	if (ft_mutex(LOCK, &philosopher->lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data))
		return (1);
	if (&philosopher->lock == philosopher->next_lock)
		return (ft_lone_philosopher(&philosopher->lock, data));
	if (ft_mutex(LOCK, philosopher->next_lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data) \
		|| ft_mutex(LOCK, &data->master_lock, data) \
		|| ft_print_event(EAT, &timestamp, philosopher->index, data))
		return (1);
	philosopher->last_meal = timestamp;
	if (ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	if (ft_has_not_finished_eating(timestamp, data))
		return (1);
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
	if (ft_mutex(LOCK, &data->master_lock, data))
		return (1);
	if (ft_print_event(SLEEP, &timestamp, philosopher->index, data))
		return (1);
	if (ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	elapsed = 0;
	while (elapsed < time_to_sleep)
	{
		if (ft_safe_usleep(data) || ft_gettime(&elapsed, data))
			return (1);
		elapsed -= timestamp;
	}
	if (ft_mutex(LOCK, &data->master_lock, data))
		return (1);
	if (ft_print_event(THINK, &timestamp, philosopher->index, data))
		return (1);
	if (ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	return (0);
}
