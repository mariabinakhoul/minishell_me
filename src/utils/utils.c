/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:26:56 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/20 12:03:17 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*smt;

	i = 0;
	smt = (char *)malloc(sizeof(char) * (n + 1));
	if (smt == NULL)
		return (NULL);
	while (i < n)
	{
		smt[i] = src[i];
		i++;
	}
	smt[i] = '\0';
	return (smt);
}

int	count_args(t_chain *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TYPE_PIPE)
	{
		if (tokens->type == TYPE_WORD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}
