/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 22:41:35 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/11 18:24:37 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/inc/libft.h"
# include <pthread.h>
# include <stdio.h>

# define BOLD_BLUE "\033[1;34m"
# define END_COLOR "\033[0m"

# define USAGE "Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[optional]<number_of_times_each_philosopher_must_eat>"
# define INVALID_ARGS "Arguments must be positive decimal integers"

#endif
