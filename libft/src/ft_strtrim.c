/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:20:11 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:30:31 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*cpy;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (ft_is_in_set(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while ((i + 1 < j) && ft_is_in_set(s1[j - 1], set))
		j--;
	cpy = malloc(j - i + 1);
	if (!cpy)
		return (NULL);
	len = j - i;
	ft_strlcpy(cpy, &s1[i], len + 1);
	return (cpy);
}
