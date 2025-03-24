/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:43:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/24 20:34:32 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_strchr(char *str, char *cmp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	if (cmp[j] == '\0' && str[i] == '\0')
// 		return (1);
// 	while (str[i])
// 	{
// 		while (str[i + j] == cmp[j] && str[i + j] && cmp[j])
// 			j++;
// 		if (cmp[j] == '\0' && str[i + j] == '\0')
// 			return (1);
// 		else
// 			j = 0;
// 		i++;
// 	}
// 	return (0);
// }

char *ft_strchr(const char *str, int c)
{
    if (!str)
        return NULL;
    while (*str) {
        if (*str == (char)c)
            return (char *)str;
        str++;
    }
    // Check if c is '\0' (standard strchr behavior)
    if ((char)c == '\0')
        return (char *)str;
    return NULL;
}