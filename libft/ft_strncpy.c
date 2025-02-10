/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:16:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/09/06 13:59:09 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *str, int nb)
{
	int		i;
	char	*array;

	i = 0;
	array = (char *)malloc(sizeof(char) * (nb + 1));
	if (array == NULL)
		return (NULL);
	while (str[i] && i < nb)
	{
		array[i] = str[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

// #include <unistd.h>

// int	main(void)
// {
// 	char src[] = "Hello, world!";
// 	char dest[20];
// 	unsigned int copied;

// 	copied = ft_strlcpy(dest, src, sizeof(dest));

// 	write(1, dest, copied);
// 	return (0);
// }