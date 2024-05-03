/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/05/03 12:07:50 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_run(t_philosopher *philosophers, int *numeric_args)
{
	int	i;

	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_thread(CREATE, &philosophers[i].thread, &philosophers[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_thread(JOIN, &philosophers[i].thread, philosophers))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_malloc(t_philosopher **philosophers, int *numeric_args)
{
	size_t			size;

	size = numeric_args[NUMBER_OF_PHILOSOPHERS] * sizeof(t_philosopher);
	*philosophers = (t_philosopher *)malloc(size);
	if (!*philosophers)
		return (ft_exit((char *)__func__, MALLOC, NULL));
	memset(*philosophers, 0, size);
	(*philosophers)->philosopher_count = numeric_args[NUMBER_OF_PHILOSOPHERS];
	return (0);
}

static int	ft_init(t_philosopher **ptr, int *numeric_args, pthread_mutex_t *master_lock)
{
	int				i;
	t_philosopher	*philosophers;

	if (ft_malloc(ptr, numeric_args))
		return (1);
	philosophers = *ptr;
	if (ft_mutex(INIT, master_lock, philosophers))
		return (1);
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_mutex(INIT, &philosophers[i].lock, philosophers))
			return (1);
		philosophers[i].master_lock = master_lock;
		philosophers[i].to_free = philosophers;
		i++;
	}
	i = 0;
	while (i + 1 < numeric_args[NUMBER_OF_PHILOSOPHERS])
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
	int				numeric_args[5];
	pthread_mutex_t	master_lock;
	t_philosopher	*philosophers;

	if (ft_check_args(ac, av, numeric_args))
		return (1);
	if (ft_init(&philosophers, numeric_args, &master_lock))
		return (1);
	if (ft_run(philosophers, numeric_args))
		return (1);
	return (ft_free(philosophers));
}
