/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/18 15:32:03 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	ft_safe_mutex_lock(philosopher->master_lock, philosopher->to_free);
	ft_safe_mutex_lock(&philosopher->lock, philosopher->to_free);
	ft_safe_mutex_lock(philosopher->next_lock, philosopher->to_free);
	ft_safe_mutex_unlock(philosopher->master_lock, philosopher->to_free);
	ft_safe_mutex_unlock(&philosopher->lock, philosopher->to_free);
	ft_safe_mutex_unlock(philosopher->next_lock, philosopher->to_free);
	return (NULL);
}

static void	ft_free(t_philosopher *to_free)
{
	size_t			i;
	
	i = 0;
	while (i < to_free->philosopher_count)
	{
		ft_safe_mutex_destroy(to_free[i].lock, NULL);
		i++;
	}
	ft_safe_mutex_destroy(to_free->master_lock, NULL);
	free(to_free);
}

void	ft_exit(char *caller_name, char *error_message, t_philosopher *to_free)
{
	if (to_free)
		ft_free(to_free);
	if (error_message)
		printf("%s%s: %s%s\n", BOLD_BLUE, caller_name, error_message, END_COLOR);
	exit(EXIT_SUCCESS);
}

static void	ft_check_args(int ac, char **av, int *numeric_args)
{
	bool	offset;
	char	*copy;
	int		num;
	int		result;

	if (ac != 5 && ac != 6)
		ft_exit((char *)__func__, USAGE, NULL);
	numeric_args[4] = -1;
	while (--ac > 0)
	{
		num = ft_atoi(av[ac]);
		copy = ft_itoa(num);
		if (!copy)
			ft_exit((char *)__func__, MALLOC, NULL);
		offset = false;
		if (av[ac][0] == '+' || av[ac][0] == '-')
			offset = true;
		result = ft_strcmp(av[ac] + offset, copy);
		free(copy);
		if (result != 0 || num == 0)
			ft_exit((char *)__func__, INVALID_ARGS, NULL);
		numeric_args[ac - 1] = num;
	}
}

int	main(int ac, char **av)
{
	/*LIBFT NOT AUTHORIZED*/
	int				i;
	int				numeric_args[5];
	pthread_mutex_t	master_lock;
	size_t			size;
	t_philosopher	*philosophers;

	ft_check_args(ac, av, numeric_args);
	size = numeric_args[NUMBER_OF_PHILOSOPHERS] * sizeof(t_philosopher);
	philosophers = (t_philosopher *)malloc(size);
	if (!philosophers)
		ft_exit((char *)__func__, MALLOC, NULL);
	memset(philosophers, 0, size);
	philosophers->philosopher_count = numeric_args[NUMBER_OF_PHILOSOPHERS];
	ft_safe_mutex_init(&master_lock, philosophers);
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		ft_safe_mutex_init(&philosophers[i].lock, philosophers);
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
		ft_safe_thread_create(&philosophers[i].thread, &ft_routine, philosophers[i]);
		i++;
	}
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		ft_safe_thread_join(philosophers[i].thread, philosophers);
		i++;
	}
	pthread_mutex_destroy(&master_lock);
	ft_safe_mutex_destroy(&master_lock, philosophers);
	memset(&master_lock, 0, sizeof(pthread_mutex_t));
	i = numeric_args[NUMBER_OF_PHILOSOPHERS];
	while (i > 0)
	{
		ft_safe_mutex_destroy(&philosophers[i - 1].lock, philosophers);
		memset(&philosophers[i - 1].lock, 0, sizeof(pthread_mutex_t));
		i--;
	}
	free(philosophers);
	return (0);
}
