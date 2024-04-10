/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:35:23 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:26:06 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int	ft_write_digit(int n)
{
	return ((n % 10) * ((n > 0) - (n < 0)));
}

char	*ft_itoa(int n)
{
	int		len;
	char	*nbr;

	len = ft_intlen(n);
	nbr = (char *)malloc(len + 1);
	if (!nbr)
		return (NULL);
	nbr[len] = '\0';
	while (n >= 10 || n <= -10)
	{
		nbr[--len] = ft_write_digit(n) + '0';
		n /= 10;
	}
	if (n < 0)
		*nbr = '-';
	nbr[--len] = ft_write_digit(n) + '0';
	return (nbr);
}
