/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:04:07 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/24 21:41:29 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char *s1, char const *s2)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (s1);
// 	i = 0;
// 	j = 0;
// 	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 		str[i++] = s2[j++];
// 	str[i] = '\0';
// 	free(s1);
// 	return (str);
// }
char *ft_strjoin(char *s1, const char *s2)
{
    char *result;
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    result = malloc(len1 + len2 + 1);  // Allocate memory for the combined string

    if (result)
    {
        strcpy(result, s1);
        strcat(result, s2);
    }
    return result;
}

