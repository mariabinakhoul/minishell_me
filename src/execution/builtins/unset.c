/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:44:09 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/07 22:45:49 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_unset(char **args, char ***envp)
{
	int		i;
	size_t	key_len;
	int		j;
	int		k;
	
	k = 0;
	i = 1;
	j = 0;
	key_len = 0;
	while(args[i])
	{
		key_len = ft_strlen(args[i]);
		j = 0;
		while ((*envp)[j])
		{
			if (ft_strncmp((*envp)[j], args[i], key_len) == 0 && (*envp)[j][key_len] == '=')
			{
				// free((*envp)[j]);
				k = j;
				while((*envp)[k])
				{
					(*envp)[k] = (*envp)[k + 1];
					k++;
				}
				(*envp)[k] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
