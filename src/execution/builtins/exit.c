/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:15 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 17:23:58 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_numeric(char *str)
{
	int	i;

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
	char			*arg;
	long long int	status;

	arg = args[1];
	printf("exit\n");
	if (!arg)
		exit(0);
	if (!is_numeric(arg) || !costum_atoi(arg, &status))
	{
		fprintf(stderr, "bash: exit: %s: numeric argument required\n", arg);
		exit(2);
	}
	if (args[2])
	{
		fprintf(stderr, "bash: exit: too many arguments\n");
		return (1);
	}
	exit((unsigned char)status);
}
