/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:19:55 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 19:31:57 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_meal_limit_reached(t_philosopher *philosopher)
{
	bool	result;
	int		meals;
	t_data	*data;

	data = philosopher->data;
	meals = data->numeric_args[NUMBER_OF_MEALS];
	if (ft_mutex(LOCK, &data->master_lock, data))
		return (1);
	result = false;
	if (philosopher->meal_count == meals)
		result = true;
	if (ft_mutex(UNLOCK, &data->master_lock, data))
		return (1);
	return (result);
}

int	ft_has_anyone_died(t_data *data)
{
	bool	result;

	if (ft_mutex(LOCK, &data->death_lock, data))
		return (1);
	result = data->death;
	if (ft_mutex(UNLOCK, &data->death_lock, data))
		return (1);
	return (result);
}

int	ft_print_event(char *event, int *timestamp, \
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

int	ft_lone_philosopher(pthread_mutex_t *lock, t_data *data)
{
	while (!ft_has_anyone_died(data))
	{
		if (ft_safe_usleep(data))
			return (1);
	}
	if (ft_mutex(UNLOCK, lock, data))
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
