/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/13 16:42:52 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_exit(char *error_message)
{
	if (error_message)
		printf("%s%s%s\n", BOLD_BLUE, error_message, END_COLOR);
	exit(EXIT_SUCCESS);
}

static void	ft_check_args(int ac, char **av, int *numeric_args)
{
	bool	offset;
	char	*copy;
	int		num;
	int		result;

	if (ac != 5 && ac != 6)
		ft_exit(USAGE);
	numeric_args[5] = -1;
	while (--ac > 0)
	{
		num = ft_atoi(av[ac]);
		copy = ft_itoa(num);
		if (!copy)
			ft_exit(MALLOC_FAIL);
		offset = false;
		if (av[ac][0] == '+' || av[ac][0] == '-')
			offset = true;
		result = ft_strcmp(av[ac] + offset, copy);
		free(copy);
		if (result != 0/* || num == 0*/)
			ft_exit(INVALID_ARGS);
		numeric_args[ac] = num;
	}
}

int	main(int ac, char **av)
{
	int			numeric_args[6];
	pthread_t	*philosophers;

	printf("%s\n", __func__);
	ft_check_args(ac, av, numeric_args);
	philosophers = (pthread_t *)malloc(numeric_args[NUMBER_OF_PHILOSOPHERS] * sizeof(pthread_t));
	if (!philosophers)
		ft_exit(MALLOC_FAIL);
	(void)av;
	return (0);
}
