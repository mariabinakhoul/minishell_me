/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:25:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/19 19:16:06 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	**safe_expand_array(void **ptr, size_t old_count, size_t new_count)
{
	void	**new_ptr;
	size_t	i;

	i = 0;
	new_ptr = malloc(sizeof(void *) * new_count);
	if (!new_ptr)
		return (NULL);
	while (i < old_count)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	i = old_count;
	while (i < new_count)
	{
		new_ptr[i] = NULL;
		i++;
	}
	free(ptr);
	return (new_ptr);
}

int	costum_atoi(const char *str, long long *out)
{
	int					sign;
	unsigned long long	result;

	*out = 0;
	result = 0;
	sign = 1;
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
		if ((sign == 1 && result > LLONG_MAX)
			|| (sign == -1 && result > (unsigned long long)LLONG_MAX + 1))
			return (0);
		str++;
	}
	*out = sign * result;
	return (1);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
