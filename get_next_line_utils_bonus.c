/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 10:57:50 by fbrisson          #+#    #+#             */
/*   Updated: 2023/01/12 14:09:24 by fbrisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*tab;

	if (nmemb > sizeof(char) * INT_MAX || size > sizeof(char) * INT_MAX)
		return (NULL);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	i = -1;
	while (++i < nmemb * size)
		tab[i] = 0;
	return (tab);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (free(s1), free(s2), NULL);
	dest = malloc(sizeof(*dest) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (free(s1), free(s2), NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	return (free(s1), dest);
}

/*

int	main(void)
{
	char	str1[] = "BABINKS ";
	char	str2[] = "AU BOUUUULOOOOOT";
	int	a;

	printf("%s", ft_strjoin(str1, str2));
	a = printf("%s", ft_strdup(str1));
	return (0);
}*/
