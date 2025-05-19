/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:06:04 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/19 19:29:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_n_flag(const char *arg)
{
	int	i;

	i = 0;
	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args, char **env)
{
	int		i;
	int		newline;
	char	*expanded_argument;

	i = 1;
	newline = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		expanded_argument = expand_argument(args[i], 0, env, 0);
		printf("%s", args[i]);
		free(expanded_argument);
		if (args[i + 1])
		{
			printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
