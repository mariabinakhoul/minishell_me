/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:43:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/09/06 15:14:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchr(char *str, char *cmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (cmp[j] == '\0' && str[i] == '\0')
		return (1);
	while (str[i])
	{
		while (str[i + j] == cmp[j] && str[i + j] && cmp[j])
			j++;
		if (cmp[j] == '\0' && str[i + j] == '\0')
			return (1);
		else
			j = 0;
		i++;
	}
	return (0);
}
