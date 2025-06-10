/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:44:09 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/06 17:11:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	remove_env_variable(char **envp, char *key)
{
	int		j;
	size_t	key_len;
	int		k;

	j = 0;
	key_len = ft_strlen(key);
	while (envp[j])
	{
		if (ft_strncmp((envp)[j], key, key_len) == 0
				&& envp[j][key_len] == '=')
		{
			free(envp[j]);
			k = j;
			while (envp[k])
			{
				envp[k] = envp[k + 1];
				k++;
			}
			envp[k] = NULL;
			return (1);
		}
		j++;
	}
	return (0);
}

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
	while (args[i])
	{
		remove_env_variable(*envp, args[i]);
		i++;
	}
	return (0);
}
