/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:32:55 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/09 16:28:07 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**sort_array(char **sorted)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (sorted[len])
		len++;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
				ft_swap(&sorted[j], &sorted[j + 1]);
			j++;
		}
		i++;
	}
	return (sorted);
}

char	**export_params(char **args, char **env)
{
	t_env	*new_export;
	char	**updated;
	t_env	*new_env;

	new_env = convert_to_list(env);
	new_export = create_node(new_env, args);
	updated = convert_to_2d(new_export);
	free_list(new_env);
	return (updated);
}

void	export_no_params(char **envp)
{
	char	**new_env;
	char	**sorted_array;

	new_env = set_env(envp);
	sorted_array = sort_array(new_env);
	print_export(sorted_array);
	free_2d(sorted_array);
}

void	print_env_value(char *env_var)
{
	int	j;

	j = 0;
	printf("=\"");
	j++;
	while (env_var[j])
	{
		printf("%c", env_var[j]);
		j++;
	}
	printf("\"");
}

void	print_export(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		printf("declare -x ");
		while (env[i][j] && env[i][j] != '=')
		{
			printf("%c", env[i][j]);
			j++;
		}
		if (env[i][j] == '=')
			print_env_value(env[i]);
		printf("\n");
		i++;
	}
}
