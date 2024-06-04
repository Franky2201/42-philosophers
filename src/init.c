/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:33:49 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 19:34:47 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_malloc(t_philosopher **philosophers, t_data *data)
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
	*philosophers = data->to_free;
	return (0);
}

int	ft_init(t_data *data)
{
	int				i;
	t_philosopher	*philosophers;

	if (ft_malloc(&philosophers, data))
		return (1);
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
