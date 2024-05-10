/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:45:27 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/10 22:04:42 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_print_event(char *event, int *timestamp, size_t philosopher, t_data *data)
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
	int		number_of_meals;
	int		time_to_die;
	size_t	i;

	number_of_meals = data->numeric_args[NUMBER_OF_MEALS];
	time_to_die = data->numeric_args[TIME_TO_DIE];
	i = 0;
	while (i < data->philosopher_count)
	{
		if (philosophers[i].meal_count != number_of_meals)
		{
			*flag = false;
			if (ft_gettime(&elapsed, data))
				return (1);
			if (ft_mutex(LOCK, &data->master_lock, data))
				return (1);
			elapsed -= philosophers[i].last_meal;
			if (ft_mutex(UNLOCK, &data->master_lock, data))
				return (1);
			if (elapsed > time_to_die)
			{
				if (ft_print_event(DIE, &elapsed, i + 1, data))
					return (1);
				if (ft_mutex(LOCK, &data->death_lock, data))
					return (1);
				data->death = true;
				if (ft_mutex(UNLOCK, &data->death_lock, data))
					return (1);
				break ;
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
	printf("eat 1\n");
	if (/*ft_mutex(LOCK, &data->master_lock, data) \
		|| */ft_mutex(LOCK, &philosopher->lock, data) \
		|| ft_print_event(FORK, &timestamp, philosopher->index, data))
		return (1);
	if (&philosopher->lock != philosopher->next_lock \
		&& (ft_mutex(LOCK, philosopher->next_lock, data) \
			|| ft_print_event(FORK, &timestamp, philosopher->index, data) \
			|| ft_print_event(EAT, &timestamp, philosopher->index, data)/* \
			|| ft_mutex(UNLOCK, &data->master_lock, data)*/))
		return (1);
	else while (!ft_has_anyone_died(data))
		ft_safe_usleep(data);
	printf("eat 2\n");
	if (ft_mutex(LOCK, &data->master_lock, data))
		return (1);
	philosopher->last_meal = timestamp;
	if (ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	elapsed = 0;
	printf("eat 3\n");
	while (elapsed < time_to_eat)
	{
		if (ft_safe_usleep(data) || ft_gettime(&elapsed, data))
			return (1);
		elapsed -= timestamp;
	}
	printf("eat 4\n");
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
	printf("sleep 1\n");
	while (elapsed < time_to_sleep)
	{
		if (ft_safe_usleep(data) || ft_gettime(&elapsed, data))
			return (1);
		elapsed -= timestamp;
	}
	printf("sleep 2\n");
	if (ft_print_event(THINK, &timestamp, philosopher->index, data))
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
	printf("health 1\n");
	//can't unlock the mutex from other thread
/*	if (data->philosopher_count == 1 \
		&& (ft_mutex(UNLOCK, &philosophers->lock, data) || ft_safe_usleep(data) \
			|| ft_mutex(UNLOCK, &philosophers->lock, data)))
			return (ptr);
*/	printf("health 2\n");
	return (NULL);
}
