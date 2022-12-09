/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:44:15 by fbrisson          #+#    #+#             */
/*   Updated: 2022/12/09 11:18:46 by fbrisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
RECUPFILE : permet de lire le fichier (read).

Pour commencer on malloc une str en fonction du buffersize.
Apres on set up un int (ouvert) a 1 et on loop en conditionnant ouvert > 0
la on read dans cet int (read(fd, str, buffer))
une secu si notre int (ouvert) < 0 read a crash (-1 quand crash)
la lu[ouvert] = 0 c'est un null terminate mais pourquoi pas '\0' ?
Ensuite on strjoin ce qu'on a lu dans le save transmis en parametre
on oublie pas de free lu vu qu'on a tout mis dans save, plus besoin
Enfin on return le save fraichement concatene du str (lu).
*/

static char	*recupfile(char *save, int fd)
{
	char	*lu;
	int		ouvert;

	lu = malloc(sizeof(*lu) * (BUFFER_SIZE + 1));
	if (!lu)
		return (NULL);
	ouvert = 1;
	while (ouvert > 0)
	{
		ouvert = read(fd, lu, BUFFER_SIZE);
		if (ouvert < 0)
		{
			free(lu);
			return (NULL);
		}
		lu[ouvert] = 0;
		save = ft_strjoin(save, lu);

	}
	free(lu);
	return (save);
}

/*
RECUPLINE : pour recuperer une seule ligne.

d'abord on verifie si save est vide.
deuxieme verrou si save[len] (mais qui vaut 0 donc pourquoi ??)
Ensuite on parcourt save tant qu'on ne trouve pas ni de \n ni \0
Si on trouve un \n on itere une fois pour bien le prendre
Ensuite petit malloc d'une str de la taille de notre iteration (len)
Ensuite on loop i < len on remplit la str du save en parametre
null terminate et return la str !
*/

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
	while (save[len] != '\n' && save[len != '\0'])
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

/*
CHECKLINE : s'occupe de gerer une seule ligne, pas les char eventuels de la ligne suivante

Tout d'abord verrou si save est vide on renvoie null
Comme dans recupline on itere jusqu'a un \n ou \0
Si on trouve un \n ++ pour le prendre
petit malloc d'un buffer selon un strlen de notre save en parametre - i (pourquoi ??) + 1 normal
ensuite on copie les char de save dans le buffer tant que l'iteration sur save me trouve pas de \0
Enfin on null terminate notre buffer, on free la save en parametre et on return le buffer
*/

static char	*checkline(char *save)
{
	char	*buffer;
	int		len;
	int		i;

	if (!save)
		return (NULL);
	len = 0;
	while (save[len] != '\n' && save[len] != '\0')
		len++;
	if (save[len] == '\n')
		len++;
	buffer = malloc(sizeof(*buffer) * (ft_strlen(save) - len) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (save[len] != '\0')
	{
		buffer[i] = save[len];
		i++;
		len++;
	}
	buffer[i] = '\0';
	free(save);
	return (buffer);
}

/*
GETNEXTLINE : La fonction principale qui permet de lire un fichier ligne par ligne

Deux char *, d'abord une save en static a laquelle on attribue un [1024]
premier verrou sur le fd bien > 0 et le buffer_size bien <= 0
Pour commencer RECUPFILE qui open read toutes les lignes du fd
Ensuite on appelle RECUPLINE qui recupere ligne par ligne et stock dans notre char line
Enfin on appelle CHECKLINE qui verifie qu'il y a bien une seule ligne dans save
et pas de caracteres en trop de la ligne suivante. Enfin return line.
*/

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

int	main(void)
{
	char	*res;
	int	fd;
	int	fd2;
	int	i = 1;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);

	while (i <= 10)
	{
		res = get_next_line(fd);
		printf("%s", res);
		free(res);
		res = get_next_line(fd2);
		printf("%s", res);
		free(res);
		i++;
	}
	close(fd);
	return (0);
}
