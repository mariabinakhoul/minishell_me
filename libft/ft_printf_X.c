/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_X.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:34:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:54 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hex__fd(unsigned long long nb, int fd)
{
	char	*maria;
	char	ans;

	maria = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_putnbr_hex__fd(nb / 16, fd);
	}
	ans = maria[nb % 16];
	write (fd, &ans, 1);
}

int	count_digits_hexxx(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

int	ft_printf__(unsigned int ptr)
{
	int	len;

	if (ptr == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	else
	{
		len = count_digits_hexxx(ptr);
		ft_putnbr_hex__fd(ptr, 1);
	}
	return (len);
}
