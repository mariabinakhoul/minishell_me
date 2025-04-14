/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:32:55 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/12 02:59:49 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	sort_array(char **sorted, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
				ft_swap(&sorted[j], &sorted[j + 1]);
			j++;
		}
		i++;
	}
}

static void	populate_sorted_array(char **sorted, t_env *env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		sorted[i] = env->data;
		env = env->next;
		i++;
	}
}

static char	**sort_envp(char **envp)
{
	int		count;
	int		i;
	char	**sorted;
	t_env	*env;

	count = 0;
	i = 0;
	env = NULL;
	env = clone_env(envp);
	while (envp[i])
	{
		count++;
		i++;
	}
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return (NULL);
	populate_sorted_array(sorted, env, count);
	sorted[count] = NULL;
	sort_array(sorted, count);
	return (sorted);
}

static void	print_export(char **envp)
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
