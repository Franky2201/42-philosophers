/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:17:31 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:28:59 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_str_count(char *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static size_t	ft_str_size(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static void	ft_strncpy(char *dest, const char *src, size_t n)
{
	dest[n] = '\0';
	while (n-- > 0)
		dest[n] = src[n];
}

static int	ft_write_strs(char **strs, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		len = ft_str_size(&s[i], c);
		if (len)
		{
			strs[j] = malloc(len + 1);
			if (!strs[j])
			{
				while (j > 0)
					free(strs[--j]);
				return (0);
			}
			ft_strncpy(strs[j++], &s[i], len);
		}
		i += len;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	len;
	char	**strs;

	if (!s)
		return (NULL);
	len = ft_str_count((char *)s, c);
	strs = (char **)malloc((len + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
	strs[len] = NULL;
	if (!ft_write_strs(strs, s, c))
	{
		free(strs);
		return (NULL);
	}
	return (strs);
}
