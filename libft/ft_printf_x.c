/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:29:02 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:47 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hexx_fd(unsigned long long nb, int fd)
{
	char	*maria;
	char	ans;

	maria = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnbr_hexx_fd(nb / 16, fd);
	}
	ans = maria[nb % 16];
	write (fd, &ans, 1);
}

int	count_digits_hexx(unsigned int nb)
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

int	ft_printf_x(unsigned int ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		write (1, "0", 1);
		return (1);
	}
	else
	{
		len = count_digits_hexx(ptr);
		ft_putnbr_hexx_fd(ptr, 1);
	}
	return (len);
}

// int main()
// {
//     int x = 1054;
// 	printf("%x", x);
//     ft_printf_x(x);
//     // ft_printf_p(NULL);
//     return 0;
// }