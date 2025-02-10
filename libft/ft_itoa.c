/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:09:03 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/06/17 15:40:23 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	length(long nb, int *sign)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		*sign *= -1;
		nb *= -1;
		count ++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

long	ft_abs(long n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	int				sign;
	long			len;
	long			f;
	char			*str;

	sign = 1;
	f = n;
	len = length(f, &sign);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	f = ft_abs(f);
	while (len >= 0)
	{
		str[len] = f % 10 + '0';
		f /= 10;
		len--;
	}
	if (sign == -1)
	{
		str[0] = '-';
	}
	return (str);
}
