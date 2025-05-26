/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:32:55 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/25 21:56:36 by mabi-nak         ###   ########.fr       */
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
	t_env	*env_list;
	char	**new_env;
	char	**sorted_array;

	new_env = set_env(envp);
	sorted_array = sort_array(new_env);
	print_export(envp);
	free_2d(new_env);
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
		{
			printf("=\"");
			j++;
			while (env[i][j])
			{
				printf("%c", env[i][j]);
				j++;
			}
			printf("\"");
		}
		printf("\n");
		i++;
	}
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg[0])
		return (0);
	if (arg[0] == '=' || (!ft_isalpha(arg[0]) && arg[0] != '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	**ft_export(char **args, char **envp)
{
	int		i;
	int		ret;
	char	**new_env;

	ret = 0;
	new_env = envp;
	if (!args[1])
	{
		export_no_params(envp);
		return (new_env);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		i++;
	}
	if (ret == 1)
		return (new_env);
	new_env = export_params(args, envp);
	return (new_env);
}

int	check_export(char **args)
{
	if (!args[1])
		return (0);
}

char	**update_envv(char **envp)
{
	return (envp);
}
