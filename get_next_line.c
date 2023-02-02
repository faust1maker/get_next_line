/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:44:15 by fbrisson          #+#    #+#             */
/*   Updated: 2023/02/02 10:16:32 by fbrisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	backn_checker(char *lu)
{
	int	i;

	i = -1;
	while (lu[++i])
		if (lu[i] == '\n')
			return (1);
	return (0);
}

static char	*recupfile(char *save, int fd)
{
	char	*lu;
	int		ouvert;

	lu = malloc(sizeof(*lu) * (BUFFER_SIZE + 1));
	if (!lu)
		return (NULL);
	ouvert = 1;
	*lu = 0;
	while (ouvert > 0 && backn_checker(lu) == 0)
	{
		ouvert = read(fd, lu, BUFFER_SIZE);
		if (ouvert < 0)
			return (free(lu), NULL);
		lu[ouvert] = '\0';
		save = ft_strjoin(save, lu);
	}
	free(lu);
	return (save);
}

static char	*recupline(char *save)
{
	char	*new_line;
	int		len;
	int		i;

	if (save == NULL)
		return (NULL);
	len = 0;
	if (save[len] == 0)
		return (NULL);
	while (save[len] != '\0' && save[len] != '\n')
		len++;
	if (save[len] == '\n')
		len++;
	new_line = malloc(sizeof(*new_line) * (len + 1));
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < len)
		new_line[i] = save[i];
	new_line[i] = '\0';
	return (new_line);
}

static char	*checkline(char *save)
{
	char	*buffer;
	int		len;
	int		i;

	if (!save)
		return (NULL);
	len = 0;
	while (save[len] != '\0' && save[len] != '\n')
		len++;
	if (save[len] == '\n')
		len++;
	if (ft_strlen(save) == 0)
		return (free(save), NULL);
	buffer = malloc(sizeof(*buffer) * (ft_strlen(save) - len) + 1);
	if (!buffer)
		return (free(save), NULL);
	i = 0;
	while (save[len] != '\0')
	{
		buffer[i] = save[len];
		i++;
		len++;
	}
	buffer[i] = '\0';
	return (free(save), buffer);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = recupfile(save[fd], fd);
	line = recupline(save[fd]);
	save[fd] = checkline(save[fd]);
	return (line);
}

/*

int	main(void)
{
	char	*res;
	char	*res2;
	int	fd;
	int	fd2;

	fd = open("emptyfile.txt", O_RDONLY);
	fd2 = open("loremipsum.txt", O_RDONLY);

	res = get_next_line(fd);
	res2 = get_next_line(fd2);
	while (res || res2)
	{
		printf("%s", res);
		free(res);
		res = get_next_line(fd);
		printf("%s", res2);
		free(res2);
		res2 = get_next_line(fd2);
	}
	close(fd);
	close(fd2);
}*/
