/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 19:35:46 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_start_threads(int i, int number_of_philosophers, \
								t_philosopher *philosophers)
{
	while (i < number_of_philosophers)
	{
		if (ft_thread(CREATE, &philosophers[i].thread, &philosophers[i]))
			return (1);
		i += 2;
	}
	return (0);
}

static int	ft_run(t_data *data)
{
	int				i;
	int				number_of_philosophers;
	t_philosopher	*philosophers;

	if (gettimeofday(&data->base_timestamp, NULL) != 0)
		return (ft_exit((char *)__func__, GETTIMEOFDAY, data));
	philosophers = data->to_free;
	number_of_philosophers = data->philosopher_count;
	i = 0;
	if (ft_start_threads(i, number_of_philosophers, philosophers))
		return (1);
	if (ft_safe_usleep(data))
		return (1);
	i = 1;
	if (ft_start_threads(i, number_of_philosophers, philosophers))
		return (1);
	i = 0;
	while (i < number_of_philosophers)
	{
		if (ft_thread(JOIN, &philosophers[i].thread, data))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	health_thread;
	t_data		data;

	memset(&data, 0, sizeof(t_data));
	if (ft_check_args(ac, av, data.numeric_args))
		return (1);
	if (ft_init(&data))
		return (1);
	if (ft_thread(HEALTH, &health_thread, data.to_free))
		return (1);
	if (ft_run(&data))
		return (1);
	if (ft_thread(JOIN, &health_thread, &data))
		return (1);
	return (ft_free(&data));
}
