/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:51:31 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/09 22:12:35 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *str)
{
	long long int				result;
	int 						sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		// printf("%lld\n", result);
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}

// #include <stdio.h>
// int main(void)
// {
// 	char s[]="-324";
// 	printf("%d\n", ft_atoi(s));
// 	return (0);
// }