/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:37:14 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/18 00:33:07 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_exit_status(int last_status, char *result)
{
	char	*status_str;

	status_str = ft_itoa(last_status);
	result = join_and_free(result, status_str);
	free(status_str);
	return (result);
}

char	*expand_env_variable(char *arg, int *i, char **env, char *result)
{
	char	*varname;
	char	*value;
	int		start;

	start = ++(*i);
	while (ft_isalnum(arg[*i]) || arg[*i] == '_')
		(*i)++;
	varname = ft_substr(arg, start, *i - start);
	value = get_env_value(varname, env);
	if (value)
		result = join_and_free(result, value);
	else
		result = join_and_free(result, "");
	free(varname);
	return (result);
}

char	*expand_variable(char *arg, int *i,
		char **env, int last_status, char *result)
{
	if (arg[*i + 1] == '?')
	{
		result = expand_exit_status(last_status, result);
		*i += 2;
	}
	else if (ft_isalpha(arg[*i + 1]) || arg[*i + 1] == '_')
		result = expand_env_variable(arg, i, env, result);
	else
		result = join_and_free_char(result, arg[(*i)++]);
	// result = exit_code;
	return (result);
}

char	*expand_home_directory(char *arg, int *i, char **env, char *result)
{
	char	*home;

	if (*i == 0 && arg[*i] == '~')
	{
		home = get_env_value("HOME", env);
		if (home)
			result = join_and_free(result, home);
		else
			result = join_and_free(result, "");
		(*i)++;
	}
	return (result);
}
