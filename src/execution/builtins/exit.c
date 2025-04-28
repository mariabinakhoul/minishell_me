/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:15 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/28 22:31:16 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;
//marc aamak
	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	char	*arg;
	int		i;
	int		status;

	i = 0;
	arg = args[1];
	if (!args[1])
	{
		printf("exit\n");
		exit(0);
	}
	//255
	if (!is_numeric(args[1]))
	{
		printf("exit\n");
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		exit (2);
	}
	if (args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		exit (1);
	}
	status = ft_atoi(arg);
	printf("exit\n");
	exit(status);
}
