/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:27:30 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 11:22:09 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	check_export_identifiers(char **args)
{
	int	i;
	int	ret;

	ret = 0;
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
	return (ret);
}

void	handle_export_arg(t_env **env_list, char *arg)
{
	if (!is_valid_identifier(arg))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		if (!args_found(*env_list, arg))
			*env_list = add_new_node(*env_list, arg);
		else
			update_value(*env_list, arg);
	}
}

t_env	*build_updated_env(char **args, char **envp)
{
	t_env	*env_list;
	int		i;

	env_list = convert_to_list(envp);
	i = 1;
	while (args[i])
	{
		handle_export_arg(&env_list, args[i]);
		i++;
	}
	return (env_list);
}

char	**ft_export(char **args, char **envp)
{
	char	**new_env;
	t_env	*updated_env;

	if (!args[1])
	{
		export_no_params(envp);
		return (envp);
	}
	updated_env = build_updated_env(args, envp);
	new_env = convert_to_2d(updated_env);
	free_list(updated_env);
	return (new_env);
}
