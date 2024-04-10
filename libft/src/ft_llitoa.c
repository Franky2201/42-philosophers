/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_llitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:20:12 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 17:49:28 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static long long int	ft_intlen(long long int n)
{
	long long int	len;

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

static long long int	ft_write_digit(long long int n)
{
	return ((n % 10) * ((n > 0) - (n < 0)));
}

char	*ft_llitoa(long long int n)
{
	long long int	len;
	char			*nbr;

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
