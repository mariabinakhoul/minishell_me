/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:44:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/14 19:46:24 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*findcommandpath(char *comand, char **envp)
{
	char	**envp_copy;
	char	**all_path;
	char	*result;
	int		i;

	result = NULL;
	envp_copy = envp;
	while (*envp_copy && !ft_strnstr(*envp_copy, "PATH=", 5))
		envp_copy++;
	if (!*envp_copy)
		return (NULL);
	all_path = ft_split(*envp_copy + 5, ':');
	i = 0;
	while (all_path[i])
	{
		result = try_build_and_access(all_path[i], comand);
		if (result)
			break ;
		i++;
	}
	freearray(all_path);
	return (result);
}

char	*try_build_and_access(const char *dir, const char *cmd)
{
	char	*with_slash;
	char	*fullpath;

	with_slash = ft_strjoin((char *)dir, "/");
	if (!with_slash)
		return (NULL);
	fullpath = ft_strjoin(with_slash, cmd);
	free(with_slash);
	if (!fullpath)
		return (NULL);
	if (access(fullpath, X_OK) == 0)
		return (fullpath);
	free(fullpath);
	return (NULL);
}

int	handle_exit_unset_export(t_ast *cmd, char ***envp_ptr)
{
	int		ret;
	char	*name;
	char	**newenv;

	ret = 0;
	name = cmd->value;
	if (ft_strcmp(name, "exit") == 0)
		ret = ft_exit(cmd->params);
	else if (ft_strcmp(name, "unset") == 0)
		ret = ft_unset(cmd->params, envp_ptr);
	else if (ft_strcmp(name, "export") == 0)
	{
		newenv = ft_export(cmd->params, *envp_ptr);
		if (newenv && newenv != *envp_ptr)
		{
			free_2d(*envp_ptr);
			*envp_ptr = newenv;
		}
		ret = 0;
	}
	return (ret);
}
