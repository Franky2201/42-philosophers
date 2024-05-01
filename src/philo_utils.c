/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:12:09 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/25 01:39:52 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	if (ft_mutex(LOCK, philosopher->master_lock, philosopher->to_free) \
		|| ft_mutex(LOCK, &philosopher->lock, philosopher->to_free) \
		|| ft_mutex(LOCK, philosopher->next_lock, philosopher->to_free))
		return ((void *)1);
	//printf("%p\n", &philosopher->lock);
//	test++;
	if (ft_mutex(UNLOCK, philosopher->master_lock, philosopher->to_free) \
		|| ft_mutex(UNLOCK, &philosopher->lock, philosopher->to_free) \
		|| ft_mutex(UNLOCK, philosopher->next_lock, philosopher->to_free))
		return ((void *)1);
	return (NULL);
}

int	ft_free(t_philosopher *to_free)
{
	size_t			i;

	i = 0;
	while (i < to_free->philosopher_count)
	{
		if (ft_mutex(DESTROY, &to_free[i].lock, NULL))
			return (1);
		i++;
	}
	if (ft_mutex(DESTROY, to_free->master_lock, NULL))
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
