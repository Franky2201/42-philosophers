/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:35:26 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:30:56 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

size_t	ft_strfind(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (i);
	}
	return (i);
}

size_t	ft_gnl_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_gnl_strcpy(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ret;

	ret = (char *)malloc(ft_gnl_strlen(s1) + ft_strfind(s2, '\n') + 1);
	if (!ret)
	{
		free((void *)s1);
		return (NULL);
	}
	i = 0;
	if (s1)
		i = ft_gnl_strcpy(ret, s1);
	j = 0;
	while (s2[j] && s2[j] != '\n')
	{
		ret[i + j] = s2[j];
		j++;
	}
	if (s2[j])
		ret[i + j++] = '\n';
	ret[i + j] = '\0';
	free((void *)s1);
	return (ret);
}
