/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:00:48 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:27:30 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	unsigned int	size;

	size = 0;
	if (!lst)
		return (size);
	while ((*lst).next)
	{
		lst = (*lst).next;
		size++;
	}
	size++;
	return (size);
}
