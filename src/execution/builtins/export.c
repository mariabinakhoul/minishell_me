/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:32:55 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/18 13:20:00 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char **sort_array(char **sorted)
{
	int i = 0, j;
	int len = 0;

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
	return sorted;
}

char **export_params(char **args,char **env)
{
	t_env *new_export;
	char **updated;
	t_env *new_env;
	new_env = convert_to_list(env);
	new_export	= create_node(new_env,args);
	// printf("*************************************\n");
	// print_env(new_export);
	// printf("*************************************\n");
	updated = convert_to_2d(new_export);
	return updated; // make this return a 2d array to use it in ft_export
}


void export_no_params(char **envp)
{
	t_env *env_list;
	char **new_env;
	char **sorted_array;
	// int i;

	// i = 0;
	new_env = set_env(envp);
	sorted_array = sort_array(new_env);
	print_export(envp);
}

void print_export(char **env)
{
	int i = 0;
	while (env[i])
	{
		int j = 0;
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
	int	i = 0;

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
	int	i;
	t_env *env;
	char **new_env;

	// i = 0;
	// env = convert_to_list(envp);
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
			ft_putstr_fd("export: not a valid identifier\n", 2);
			return (new_env);
		}
		i++;
	}
	new_env = export_params(args,envp); //we need it char "** " for set env
		// print_export(new_env);	
	return (new_env);
}

int check_export(char **args)
{
	if (!args[1])
		return 0;
}

char **update_envv(char **envp) //make a function that updates the env rvry time withut execution everytime
{
	return envp;
}