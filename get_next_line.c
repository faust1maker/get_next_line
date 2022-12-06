/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:44:15 by fbrisson          #+#    #+#             */
/*   Updated: 2022/12/06 10:05:11 by fbrisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	yabackn(char *save)
{
	if (save)
	{
		while (*save)
		{
			if (*save == '\n')
				return (0);
			save++;
		}
	}
	return (1);
}

char	*ft_read(int fd, char *save)
{
	char	*buffer;

	while (yabackn(save) && read > 0)
	{

	}
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = read(fd, save, BUFFER_SIZE);
	if (!save)
		return (NULL);
	line = // NEW LINE / NEXT LINE ?
	save = // CLEANER ?
	return (line);
}
