/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:12:09 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/03 18:06:07 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_print_event(char *event, size_t philosopher, t_data *data)
{
	int	seconds;
	int	milliseconds;

	/* gettimeofday and compare with base_time */
	printf("%i%i %zu %s\n" philosopher, event);
}

static int	ft_eat(t_philosopher *philosopher, t_data *data)
{
	if (ft_mutex(LOCK, &philosopher->lock, data))
		return (1);
	printf("%i %zu %s\n" philosopher->index, FORK);
	if (ft_mutex(LOCK, philosopher->next_lock, data))
		return (1);
}

void	*ft_routine(void *ptr)
{
	t_data			*data;
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)ptr;
	data = philosopher->data;
	if (ft_mutex(LOCK, &data->master_lock, data) \
		|| ft_mutex(LOCK, &philosopher->lock, data) \
		|| ft_mutex(LOCK, philosopher->next_lock, data))
		return ((void *)1);
	//printf("%p\n", &philosopher->lock);
	if (ft_mutex(UNLOCK, &data->master_lock, data) \
		|| ft_mutex(UNLOCK, &philosopher->lock, data) \
		|| ft_mutex(UNLOCK, philosopher->next_lock, data))
		return ((void *)1);
	return (NULL);
}

int	ft_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		return (ft_exit((char *)__func__, GETTIMEOFDAY, data));
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
	if (ft_mutex(DESTROY, &data->master_lock, NULL))
		return (1);
	free(to_free);
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
