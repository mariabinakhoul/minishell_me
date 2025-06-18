/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:27:30 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/18 15:25:45 by mabi-nak         ###   ########.fr       */
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

char	**ft_export(char **args, char **envp)
{
	int		ret;
	char	**new_env;

	ret = 0;
	new_env = envp;
	if (!args[1])
	{
		export_no_params(envp);
		return (new_env);
	}
	ret = check_export_identifiers(args);
	if (ret == 1)
		return (new_env);
	new_env = export_params(args, envp);
	return (new_env);
}
