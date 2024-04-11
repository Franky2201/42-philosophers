/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:42:34 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/11 18:26:46 by gde-win          ###   ########.fr       */
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
			ft_exit("ft_itoa: malloc failure");
		offset = false;
		if (av[ac][0] == '+' || av[ac][0] == '-')
			offset = true;
		result = ft_strcmp(av[ac] + offset, copy);
		free(copy);
		if (result != 0)
			ft_exit(INVALID_ARGS);
		numeric_args[ac] = num;
	}
}

int	main(int ac, char **av)
{
	int	numeric_args[6];

	ft_check_args(ac, av, numeric_args);
	(void)av;
	return (0);
}
