/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/03 19:17:37 by gde-win          ###   ########.fr       */
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

static int	ft_malloc(t_data *data)
{
	int				*numeric_args;
	size_t			size;

	numeric_args = data->numeric_args;
	size = numeric_args[NUMBER_OF_PHILOSOPHERS] * sizeof(t_philosopher);
	data->to_free = (t_philosopher *)malloc(size);
	if (!data->to_free)
		return (ft_exit((char *)__func__, MALLOC, NULL));
	memset(data->to_free, 0, size);
	data->philosopher_count = numeric_args[NUMBER_OF_PHILOSOPHERS];
	return (0);
}

static int	ft_init(t_data *data)
{
	int				i;
	t_philosopher	*philosophers;

	if (ft_malloc(data))
		return (1);
	philosophers = data->to_free;
	if (ft_mutex(INIT, &data->master_lock, data) \
		|| ft_mutex(INIT, &data->death_lock, data))
		return (1);
	i = 0;
	while (i < data->numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_mutex(INIT, &philosophers[i].lock, data))
			return (1);
		philosophers[i].data = data;
		philosophers[i].index = i + 1;
		i++;
	}
	i = 0;
	while (i + 1 < data->numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		philosophers[i].next_lock = &philosophers[i + 1].lock;
		i++;
	}
	philosophers[i].next_lock = &philosophers[0].lock;
	return (0);
}

static int	ft_check_args(int ac, char **av, int *numeric_args)
{
	bool	offset;
	char	*copy;
	int		num;
	int		result;

	if (ac != 5 && ac != 6)
		return (ft_exit((char *)__func__, USAGE, NULL));
	numeric_args[4] = -1;
	while (--ac > 0)
	{
		num = ft_atoi(av[ac]);
		copy = ft_itoa(num);
		if (!copy)
			return (ft_exit((char *)__func__, MALLOC, NULL));
		offset = false;
		if (av[ac][0] == '+' || av[ac][0] == '-')
			offset = true;
		result = ft_strcmp(av[ac] + offset, copy);
		free(copy);
		if (result != 0 || num == 0)
			return (ft_exit((char *)__func__, INVALID_ARGS, NULL));
		numeric_args[ac - 1] = num;
	}
	return (0);
}

int	main(int ac, char **av)
{
	/*LIBFT NOT AUTHORIZED*/
	pthread_t		health_thread;
	t_data			data;

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
