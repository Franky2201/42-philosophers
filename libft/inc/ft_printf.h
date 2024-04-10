/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:45:15 by gde-win           #+#    #+#             */
/*   Updated: 2024/02/20 20:11:37 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

int		ft_printf(const char *fmt, ...);
void	ft_printf_putchar(char c, ssize_t *len);
void	ft_printf_putnbr(int n, ssize_t *len);
void	ft_printf_putstr(char *s, ssize_t *len);

#endif
