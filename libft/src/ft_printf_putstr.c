/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:27:35 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:28:34 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_printf_putstr(char *s, ssize_t *len)
{
	size_t	length;

	if (!s)
	{
		if (write(1, "(null)", 6) == -1)
			*len = -1;
		else
			*len += 6;
		return ;
	}
	length = ft_strlen(s);
	if (write(1, s, length) == -1)
		*len = -1;
	else
		*len += length;
}
