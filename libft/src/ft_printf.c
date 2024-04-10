/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:26:09 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:28:08 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static void	ft_putnbr_hex(unsigned long long int n, char upcase, ssize_t *len)
{
	unsigned char	c;

	if (upcase != 'p')
		n = (unsigned int)n;
	if (n >= 16)
		ft_putnbr_hex(n / 16, upcase, len);
	if (n < 16 && upcase == 'p')
	{
		write(1, "0x", 2);
		*len += 2;
	}
	n %= 16;
	if (n > 9)
		c = (n - 10 + 'A') | 040 * (upcase != 'X');
	else
		c = n + '0';
	write(1, &c, 1);
	(*len)++;
}

static void	ft_putunbr(unsigned int n, ssize_t *len)
{
	unsigned char	c;

	if (n >= 10)
		ft_putunbr(n / 10, len);
	n %= 10;
	c = n + '0';
	write (1, &c, 1);
	(*len)++;
}

static void	ft_format(char c, va_list *args, ssize_t *len)
{
	if (c == '%')
		ft_printf_putchar('%', len);
	else if (c == 'c')
		ft_printf_putchar((char)va_arg(*args, int), len);
	else if (c == 's')
		ft_printf_putstr(va_arg(*args, char *), len);
	else if (c == 'p' || c == 'x' || c == 'X')
		ft_putnbr_hex(va_arg(*args, unsigned long long int), c, len);
	else if (c == 'd' || c == 'i')
		ft_printf_putnbr(va_arg(*args, int), len);
	else if (c == 'u')
		ft_putunbr(va_arg(*args, unsigned int), len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	size_t		i;
	ssize_t		len;

	if (!fmt)
		return (0);
	va_start(args, fmt);
	i = 0;
	len = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			ft_format(fmt[i], &args, &len);
		}
		else
			ft_printf_putchar((char)fmt[i], &len);
		if (len == -1)
			return (-1);
		i++;
	}
	va_end(args);
	return ((int)(len));
}
