/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/17 20:03:43 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*ft_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	ft_safe_mutex_lock(philosopher->master_lock, philosophers);
	pthread_mutex_lock(philosopher->master_lock);
	pthread_mutex_lock(&philosopher->lock);
	pthread_mutex_lock(philosopher->next_lock);
	pthread_mutex_unlock(philosopher->master_lock);
	printf("%i\n", philosopher->i);
	pthread_mutex_unlock(&philosopher->lock);
	pthread_mutex_unlock(philosopher->next_lock);
	return (NULL);
}

static void	ft_exit(char *caller_name, char *error_message)
{
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
		ft_exit((char *)__func__, USAGE);
	numeric_args[4] = -1;
	while (--ac > 0)
	{
		num = ft_atoi(av[ac]);
		copy = ft_itoa(num);
		if (!copy)
			ft_exit((char *)__func__, MALLOC);
		offset = false;
		if (av[ac][0] == '+' || av[ac][0] == '-')
			offset = true;
		result = ft_strcmp(av[ac] + offset, copy);
		free(copy);
		if (result != 0 || num == 0)
			ft_exit((char *)__func__, INVALID_ARGS);
		numeric_args[ac - 1] = num;
	}
}

int	main(int ac, char **av)
{
	/*LIBFT NOT AUTHORIZED*/
	int				i;
	int				numeric_args[5];
	pthread_mutex_t	master_lock;
	t_philosopher	*philosophers;

	ft_check_args(ac, av, numeric_args);
	philosophers = (t_philosopher *)malloc(numeric_args[NUMBER_OF_PHILOSOPHERS] * sizeof(t_philosopher));
	if (!philosophers)
		ft_exit((char *)__func__, MALLOC);
	ft_safe_mutex_init(&master_lock, philosophers);
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		ft_safe_mutex_init(&philosophers[i].lock, philosophers);
		philosophers[i].master_lock = &master_lock;
		philosophers[i].i = i;
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
		ft_safe_thread_create(&philosophers[i].thread, &ft_routine, philosophers, i);
		i++;
	}
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		ft_safe_thread_join(philosophers[i].thread, philosophers);
		i++;
	}
	pthread_mutex_destroy(&master_lock);
	i = 0;
	while (i < numeric_args[NUMBER_OF_PHILOSOPHERS])
	{
		ft_safe_mutex_destroy(&philosophers[i].lock);
		i++;
	}
	free(philosophers);
	return (0);
}
