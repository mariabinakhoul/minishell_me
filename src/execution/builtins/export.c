/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:32:55 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/09 19:30:49 by nhaber           ###   ########.fr       */
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

char **export_params(char **args,t_env *env)
{
	t_env *new_export;
	char **updated;

	new_export	= create_node(env,args);
	printf("*************************************\n");
	print_env(new_export);
	printf("*************************************\n");
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
	int i;

	i = 0;
	while (env[i])
	{
		printf("declare -x \"%s\"\n", env[i]);
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

// static char	**sort_envp(char **envp)
// {
// 	int		count;
// 	int		i;
// 	char	**sorted;
// 	t_env	*env;

// 	count = 0;
// 	i = 0;
// 	env = NULL;
// 	env = clone_env(envp);
// 	while (envp[i])
// 	{
// 		count++;
// 		i++;
// 	}
// 	sorted = malloc(sizeof(char *) * (count + 1));
// 	if (!sorted)
// 		return (NULL);
// 	populate_sorted_array(sorted, env, count);
// 	sorted[count] = NULL;
// 	sort_array(sorted, count);
// 	return (sorted);
// }

// static void	print_export(char **envp)
// {
// 	char	**sorted;
// 	int		i;

// 	i = 0;
// 	sorted = sort_envp(envp);
// 	while (sorted[i])
// 	{
// 		printf("declare -x \"%s\"\n", sorted[i]);
// 		i++;
// 	}
// }

// int	is_valid_identifier(char *arg)
// {
// 	int	i;

// 	i = 0;
// 	if (!arg || !arg[0])
// 		return (0);
// 	if (arg[0] == '=' || (!ft_isalpha(arg[0]) && arg[0] != '_'))
// 		return (0);
// 	while (arg[i] && arg[i] != '=')
// 	{
// 		if (!ft_isalnum(arg[i]) && arg[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int	ft_export(char **args, char **envp)
// {
// 	int	i;

// 	i = 1;
// 	if (!args[1])
// 	{
// 		print_export(envp);
// 		return (0);
// 	}
// 	while (args[i])
// 	{
// 		if (!is_valid_identifier(args[i]))
// 		{
// 			printf("export: not a valid identifier\n");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

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

int	ft_export(char **args, char **envp)
{
	int	i;
	t_env *env;
	char **new_env;
	env = convert_to_list(envp);
	if (!args[1])
	{
		export_no_params(envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("export: not a valid identifier\n", 2);
			return (1);
		}
		else
		{
			new_env = export_params(args,env); //we need it char "** " for set env
			// print_export(new_env);
		}
		i++;
	}
	return (0);
}
