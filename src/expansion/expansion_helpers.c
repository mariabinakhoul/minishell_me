/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 04:37:14 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 17:03:43 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_exit_status(int exit_code, char *result)
{
	char	*status_str;

	status_str = ft_itoa(exit_code);
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

char	*expand_variable(char *arg, t_expand *two_in_one,
		char **env, int exit_code)
{
	char	*result;
	int		*i;

	result = two_in_one->result;
	i = two_in_one->i;
	if (arg[*i + 1] == '?')
	{
		result = expand_exit_status(exit_code, result);
		*i += 2;
	}
	else if (ft_isalpha(arg[*i + 1]) || arg[*i + 1] == '_')
		result = expand_env_variable(arg, i, env, result);
	else if (ft_isdigit(arg[*i + 1]))
		*i += 2;
	else
		result = join_and_free_char(result, arg[(*i)++]);
	return (result);
}

char	*expand_home_directory(char *arg, int *i, char **env)
{
	char	*home;

	if (*i == 0 && arg[*i] == '~')
	{
		(*i)++;
		home = get_env_value("HOME", env);
		if (home)
			return (ft_strdup(home));
		else
			return (ft_strdup(""));
	}
	return (NULL);
}
