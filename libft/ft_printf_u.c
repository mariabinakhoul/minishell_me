/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:17:32 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:34 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_u_fd(unsigned int nb, int fd)
{
	char	ans;

	if (nb >= 10)
	{
		ft_putnbr_u_fd(nb / 10, fd);
	}
	ans = nb % 10 + '0';
	write (fd, &ans, 1);
}

int	count_digits_u(unsigned int c)
{
	int	count;

	count = 0;
	if (c == 0)
		return (1);
	while (c > 0)
	{
		c /= 10;
		count++;
	}
	return (count);
}

int	ft_printf_u(unsigned int c)
{
	int	len;

	len = count_digits_u(c);
	ft_putnbr_u_fd(c, 1);
	return (len);
}
