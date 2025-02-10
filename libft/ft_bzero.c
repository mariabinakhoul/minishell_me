/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:22:43 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/06/13 10:05:50 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

// #include <stdio.h>
// int main() 
// {
//     char buffer[10] = "Hello";
//     size_t size = 5;

//     ft_bzero(buffer, size);
//     printf("After bzero: %s\n", buffer);
//     return (0);
// }
