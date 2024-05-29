/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:45:27 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/29 18:08:03 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_print_event(char *event, int *timestamp, \
				size_t philosopher, t_data *data)
{
	if (ft_gettime(timestamp, data))
		return (1);
	if (ft_has_anyone_died(data))
		return (0);
	if (printf("%i\t%zu\t%s\n", *timestamp, philosopher, event) < 0)
		return (ft_exit((char *)__func__, PRINTF, data));
	return (0);
}

static int	ft_die(t_philosopher *philosophers, t_data *data, bool *flag)
{
	int		elapsed;
	int		time_to_die;
	size_t	i;

	time_to_die = data->numeric_args[TIME_TO_DIE];
	i = 0;
	while (i < data->philosopher_count)
	{
		if (!ft_meal_limit_reached(&philosophers[i]))
		{
			if (ft_mutex(UNLOCK, &data->master_lock, data))
				return (1);
			*flag = false;
			if (ft_gettime(&elapsed, data))
				return (1);
			elapsed -= philosophers[i].last_meal;
			if (elapsed >= time_to_die)
			{
				if (ft_mutex(LOCK, &data->master_lock, data))
					return (1);
				if (ft_print_event(DIE, &elapsed, i + 1, data))
					return (1);
				if (ft_mutex(LOCK, &data->death_lock, data))
					return (1);
				data->death = true;
				if (ft_mutex(UNLOCK, &data->death_lock, data))
					return (1);
				if (ft_mutex(UNLOCK, &data->master_lock, data))
					return (1);
				return (0);
			}
		}
		i++;
	}
	return (0);
}

int	ft_eat(t_philosopher *philosopher, t_data *data)
{
	int	elapsed;
	int	time_to_eat;
	int	timestamp;

	time_to_eat = data->numeric_args[TIME_TO_EAT];
	if (ft_mutex(LOCK, &philosopher->lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data))
		return (1);
	if (&philosopher->lock == philosopher->next_lock)
	{
		while (!ft_has_anyone_died(data))
		{
			if (ft_safe_usleep(data))
				return (1);
		}
		if (ft_mutex(UNLOCK, &philosopher->lock, data))
			return (1);
		return (0);
	}
	if (ft_mutex(LOCK, philosopher->next_lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data) \
		|| ft_mutex(LOCK, &data->master_lock, data) \
		|| ft_print_event(EAT, &timestamp, philosopher->index, data) \
		|| ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	//data race
	philosopher->last_meal = timestamp;
	elapsed = 0;
	while (elapsed < time_to_eat)
	{
		if (ft_safe_usleep(data) || ft_gettime(&elapsed, data))
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

void	*ft_healthcheck(void *ptr)
{
	bool			flag;
	t_data			*data;
	t_philosopher	*philosophers;

	philosophers = (t_philosopher *)ptr;
	data = philosophers->data;
	flag = false;
	while (!ft_has_anyone_died(data) && !flag)
	{
		flag = true;
		if (ft_safe_usleep(data))
			return (ptr);
		if (ft_die(philosophers, data, &flag))
			return (ptr);
	}
	return (NULL);
}
