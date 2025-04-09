/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:15 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/09 21:19:13 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]) && !(i == 0 && arg[i] == '-'))
		{
			ft_putstr_fd("bash: exit: %s numeric argument required\n", 2);
			exit (2);
		}
		i++;
	}
	status = ft_atoi(arg);
	printf("exit\n");
	exit(status);
}
