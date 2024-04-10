/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-win <gde-win@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:41:57 by gde-win           #+#    #+#             */
/*   Updated: 2024/04/10 19:30:47 by gde-win          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

void	ft_update(char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	j = 0;
	while (buffer[i])
	{
		i++;
		buffer[j] = buffer[i];
		j++;
	}
	while (buffer[j])
	{
		buffer[j] = '\0';
		j++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffers[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	ssize_t		i;

	line = NULL;
	while (true)
	{
		if (ft_gnl_strlen(buffers[fd]) == 0)
		{
			i = read(fd, buffers[fd], BUFFER_SIZE);
			if (i == -1)
			{
				free(line);
				return (NULL);
			}
			else if (i == 0)
				return (line);
		}
		line = ft_gnl_strjoin(line, buffers[fd]);
		if (line == NULL)
			return (NULL);
		ft_update(buffers[fd]);
		if (line[ft_gnl_strlen(line) - 1] == '\n')
			return (line);
	}
}
