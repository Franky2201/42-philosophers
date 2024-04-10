/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:31:48 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:27:20 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*cpy;

	if (!lst || !f || !del)
		return (NULL);
	cpy = (t_list *)malloc(sizeof(t_list));
	if (!cpy)
		return (NULL);
	cpy->content = f(lst->content);
	lst = lst->next;
	node = cpy;
	while (lst)
	{
		node->next = (t_list *)malloc(sizeof(t_list));
		if (!node->next)
		{
			ft_lstclear(&cpy, del);
			return (NULL);
		}
		node = node->next;
		node->content = f(lst->content);
		lst = lst->next;
	}
	node->next = NULL;
	return (cpy);
}
