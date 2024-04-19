/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/19 18:18:09 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	test = 0;

void	*ft_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	if (ft_safe_mutex_lock(philosopher->master_lock, philosopher->to_free) \
		|| ft_safe_mutex_lock(&philosopher->lock, philosopher->to_free) \
		|| ft_safe_mutex_lock(philosopher->next_lock, philosopher->to_free))
		return ((void *)1);
	//printf("%p\n", &philosopher->lock);
	test++;
	if (ft_safe_mutex_unlock(philosopher->master_lock, philosopher->to_free) \
		|| ft_safe_mutex_unlock(&philosopher->lock, philosopher->to_free) \
		|| ft_safe_mutex_unlock(philosopher->next_lock, philosopher->to_free))
		return ((void *)1);
	return (NULL);
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

static int	ft_free(t_philosopher *to_free)
{
	size_t			i;
	
	i = 0;
	while (i < to_free->philosopher_count)
	{
		if (ft_safe_mutex_destroy(&to_free[i].lock, NULL))
			return (1);
		i++;
	}
	if (ft_safe_mutex_destroy(to_free->master_lock, NULL))
		return (1);
	free(to_free);
	return (0);
}

int	ft_exit(char *caller_name, char *error_message, t_philosopher *to_free)
{
	if (to_free)
		ft_free(to_free);
	if (error_message)
		printf("%s%s: %s%s\n", BOLD_BLUE, caller_name, error_message, END_COLOR);
	return (1);
}

int	main(int ac, char **av)
{
	/*LIBFT NOT AUTHORIZED*/
	int				i;
	int				numeric_args[5];
	pthread_mutex_t	master_lock;
	t_philosopher	*philosophers;

	if (ft_check_args(ac, av, numeric_args))
		return (1);
	if (ft_malloc(&philosophers, numeric_args))
		return (1);
	if (ft_safe_mutex_init(&master_lock, philosophers))
		return (1);
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_safe_mutex_init(&philosophers[i].lock, philosophers))
			return (1);
		philosophers[i].master_lock = &master_lock;
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
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_safe_thread_create(&philosophers[i].thread, &ft_routine, &philosophers[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		if (ft_safe_thread_join(philosophers[i].thread, philosophers))
			return (1);
		i++;
	}
	return (ft_free(philosophers));
}
