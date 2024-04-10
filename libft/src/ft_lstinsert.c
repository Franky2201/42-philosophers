/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 20:12:43 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:27:04 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstinsert(t_list **lst, t_list *new)
{
	t_list	*next;

	if (lst && new)
	{
		if (*lst)
		{
			next = (*lst)->next;
			(*lst)->next = new;
			new->previous = *lst;
			new->next = next;
			next->previous = new;
		}
		else
			*lst = new;
	}
}
