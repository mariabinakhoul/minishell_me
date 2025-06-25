/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:54:23 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/25 15:55:12 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(char **envp)
{
	char	**environment;
	int		i;

	i = 0;
	environment = set_env(envp);
	while (environment[i])
	{
		if (ft_strchr(environment[i], '='))
			printf("%s\n", environment[i]);
		i++;
	}
	free_2d(environment);
}
