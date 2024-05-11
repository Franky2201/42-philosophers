/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:12:09 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/11 19:44:58 by gde-win          ###   ########.fr       */
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

void	*ft_routine(void *ptr)
{
	int				meals;
	t_data			*data;
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)ptr;
	data = philosopher->data;
	meals = data->numeric_args[NUMBER_OF_MEALS];
	while (!ft_meal_limit_reached(philosopher) && !ft_has_anyone_died(data))
	{
		if (ft_eat(philosopher, data))
			return (ptr);
		if (ft_mutex(LOCK, &data->master_lock, data))
			return (ptr);
		if (philosopher->meal_count < meals)
			philosopher->meal_count++;
		if (ft_mutex(UNLOCK, &data->master_lock, data))
			return (ptr);
		if (ft_sleep(philosopher, data))
			return (ptr);
	}
	return (NULL);
}

int	ft_safe_usleep(t_data *data)
{
	if (usleep(500) != 0)
		return (ft_exit((char *)__func__, USLEEP, data));
	return (0);
}

int	ft_gettime(int *timestamp, t_data *data)
{
	int				seconds;
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (ft_exit((char *)__func__, GETTIMEOFDAY, data));
	seconds = time.tv_sec - data->base_timestamp.tv_sec;
	*timestamp = (time.tv_usec - data->base_timestamp.tv_usec) / 1000;
	*timestamp += seconds * 1000;
	return (0);
}

int	ft_free(t_data *data)
{
	size_t			i;
	t_philosopher	*to_free;

	to_free = data->to_free;
	i = 0;
	while (i < data->philosopher_count)
	{
		if (ft_mutex(DESTROY, &to_free[i].lock, NULL))
			return (1);
		i++;
	}
	if (ft_mutex(DESTROY, &data->death_lock, NULL) \
		|| ft_mutex(DESTROY, &data->master_lock, NULL))
		return (1);
	free(to_free);
	data->to_free = NULL;
	return (0);
}

int	ft_exit(char *caller_name, char *error_message, t_data *data)
{
	if (data && data->to_free)
		ft_free(data);
	if (error_message)
		printf("%s%s: %s%s\n", BOLD_BLUE, caller_name, error_message, END_COLOR);
	return (1);
}
