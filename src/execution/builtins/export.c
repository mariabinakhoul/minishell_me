/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:32:55 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/08 22:51:38 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


void	ft_swap(char **a, char **b)
{
	char	*tmp;

	*tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**sort_envp(char **envp)
{
	int		count = 0;
	int		i = 0;
	int		j;
	char	**sorted;

	t_env *env = NULL;
	env = clone_env(envp);
	while (envp[i])
	{
		count++;
		i++;
	}
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted[i] = env->data;
		env = env->next;
		i++;
	}
	sorted[count] = NULL;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted[j],sorted[j + 1]) > 0)
				ft_swap(&sorted[j], &sorted[j + 1]);
			j++;
		}
		i++;
	}
	return (sorted);
}

void	print_export(char **envp)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = sort_envp(envp);
	while (sorted[i])
	{
		printf("declare -x \"%s\"\n", sorted[i]);
		i++;
	}
}

void	ft_export(char **envp)
{
	print_export(envp);
}
