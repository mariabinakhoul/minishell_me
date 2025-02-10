/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:19:46 by mabi-nak          #+#    #+#             */
/*   Updated: 2024/09/20 22:30:29 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd(char *str, char buff)
{
	int		i;
	char	*array;

	i = 0;
	array = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (array == NULL)
		return (NULL);
	while (str[i])
	{
		array[i] = str[i];
		i++;
	}
	free(str);
	array[i] = buff;
	array[++i] = '\0';
	return (array);
}

int	get_next_line(int fd, char **str)
{
	char	buff;
	int		i;

	i = read(fd, &buff, 1);
	while (i > 0)
	{
		*str = ft_stradd(*str, buff);
		if (buff == '\n')
			return (i);
		else
			i++;
		i = read(fd, &buff, 1);
	}
	if (i == 0)
	{
		free(*str);
		*str = NULL;
	}
	return (i);
}
