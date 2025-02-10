/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:45:00 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/07/16 13:55:17 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hexp_fd(unsigned long long nb, int fd)
{
	char	*maria;
	char	ans;

	maria = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_putnbr_hexp_fd(nb / 16, fd);
	}
	ans = maria[nb % 16];
	write (fd, &ans, 1);
}

int	ft_printf_p(void *ptr)
{
	unsigned long long	str;
	int					len;

	str = (unsigned long long) ptr;
	len = 0;
	if (str == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	else
	{
		write (1, "0x", 2);
		len += 2;
		ft_putnbr_hexp_fd(str, 1);
		while (str > 0)
		{
			len++;
			str /= 16;
		}
	}
	return (len);
}

// int main()
// {
//     int x = 42;
// 	printf("%p", &x);
//     ft_printf_p(&x);
//     // ft_printf_p(NULL);
//     return 0;
// }