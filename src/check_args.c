/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:28:00 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 16:43:25 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_check_args(int ac, char **av, int *numeric_args)
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
