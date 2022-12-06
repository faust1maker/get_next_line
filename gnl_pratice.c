/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_pratice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbrisson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:26:27 by fbrisson          #+#    #+#             */
/*   Updated: 2022/12/05 10:15:02 by fbrisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return;
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
}

void	ft_putnbr(int nb)
{
	long int	lnb;
	long int	div;
	long int	mod;

	lnb = nb;
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar(45);
	}
	div = lnb / 10;
	mod = lnb % 10;
	if (div != 0)
		ft_putnbr(div);
	ft_putchar(48 + mod);
}

int	main(void)
{
	char	buffer[BUFFER_SIZE + 1];
	int	fd;
	int	return_value;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("open() error");
		return (1);
	}
	while (return_value = read(fd, buffer, BUFFER_SIZE))
	{
		buffer[return_value] = '\0';
		ft_putnbr(return_value);
		ft_putstr(buffer);
	}
	ft_putnbr(return_value);
	ft_putstr(buffer);
	if (close(fd) == -1)
	{
		ft_putstr("close() error()");
		return (1);
	}
	return (0);
}
