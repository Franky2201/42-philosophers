/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:31:45 by gde-win           #+#    #+#             */
/*   Updated: 2024/06/04 16:43:01 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	sum;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	sum = 0;
	while (ft_isdigit(str[i]))
	{
		sum = sum * 10 + (str[i++] - '0');
		if (sum < 0)
		{
			if (sign < 0)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
	}
	sum *= sign;
	return ((int)sum);
}
