/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhorefto <lhorefto@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:44:59 by lhorefto          #+#    #+#             */
/*   Updated: 2021/07/04 16:53:28 by lhorefto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	ft_putstr_fd(const char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_printerror(const char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}
