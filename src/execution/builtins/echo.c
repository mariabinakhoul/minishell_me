/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 19:06:04 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/22 13:12:36 by nhaber           ###   ########.fr       */
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
		// if (args[i] == '\'\'' || args[i] == '\"\"')
		// 	i++;
		expanded_argument = expand_argument(args[i], 0, env, 0);
		printf("%s", args[i]);
		free(expanded_argument);
		if (args[i] != '\'\'' || (strcmp (args[i] ,'\"\"') == 0))
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
