/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 00:12:09 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/25 00:32:30 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *data)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)data;
	if (ft_safe_mutex_lock(philosopher->master_lock, philosopher->to_free) \
		|| ft_safe_mutex_lock(&philosopher->lock, philosopher->to_free) \
		|| ft_safe_mutex_lock(philosopher->next_lock, philosopher->to_free))
		return ((void *)1);
	//printf("%p\n", &philosopher->lock);
//	test++;
	if (ft_safe_mutex_unlock(philosopher->master_lock, philosopher->to_free) \
		|| ft_safe_mutex_unlock(&philosopher->lock, philosopher->to_free) \
		|| ft_safe_mutex_unlock(philosopher->next_lock, philosopher->to_free))
		return ((void *)1);
	return (NULL);
}

int	ft_exit(char *caller_name, char *error_message, t_philosopher *to_free)
{
	if (to_free)
		ft_free(to_free);
	if (error_message)
		printf("%s%s: %s%s\n", BOLD_BLUE, caller_name, error_message, END_COLOR);
	return (1);
}
