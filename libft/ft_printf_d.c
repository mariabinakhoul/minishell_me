/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:45:41 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:06 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	ans;

	if (nb == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	ans = nb % 10 + '0';
	write (fd, &ans, 1);
}

int	count_digits(int c)
{
	int	count;

	count = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		count++;
		c = -c;
	}
	while (c > 0)
	{
		c /= 10;
		count++;
	}
	return (count);
}

int	ft_printf_d(int c)
{
	int	len;

	if (c == -2147483648)
		len = 11;
	else
		len = count_digits(c);
	ft_putnbr_fd(c, 1);
	return (len);
}
