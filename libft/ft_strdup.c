/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:48:06 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/09/04 16:58:41 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		len;
	int		i;
	char	*smt;

	i = 0;
	len = ft_strlen(src);
	smt = (char *)malloc(sizeof(char) * (len + 1));
	if (smt == NULL)
		return (NULL);
	while (src[i])
	{
		smt[i] = src[i];
		i++;
	}
	smt[i] = '\0';
	return (smt);
}

// #include <stdio.h>
// int main(void)
// {
// 	char *src = "maria is the best";

// 	printf("%s\n", ft_strdup(src));
// 	return (0);
// }