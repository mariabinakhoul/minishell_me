/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:37:15 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/09 22:30:31 by nhaber           ###   ########.fr       */
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

int safe_atoi(const char *str, long long *out)
{
	int sign = 1;
	unsigned long long result = 0;

	*out = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > LLONG_MAX) ||
			(sign == -1 && result > (unsigned long long)LLONG_MAX + 1))
			return (0);
		str++;
	}
	*out = sign * result;
	return (1);
}


int	ft_exit(char **args)
{
	char			*arg;
	long long int	status;
	int				is_valid;

	arg = args[1];
	printf("exit\n");

	if (!arg)
		exit(0);

	if (!is_numeric(arg) || !safe_atoi(arg, &status))
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

