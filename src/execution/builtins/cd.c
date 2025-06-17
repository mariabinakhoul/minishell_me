/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 17:22:44 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*retrieve_env_path(t_ast *cmd, char **envp, char *key)
{
	char	*path;
	int		i;

	i = 0;
	if (!cmd || !envp || !key)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
		{
			path = &envp[i][ft_strlen(key) + 1];
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_home_or_oldpwd(t_ast *cmd, char **envp)
{
	char	*path;

	if (!cmd->params[1])
	{
		path = retrieve_env_path(cmd, envp, "HOME");
		if (!path)
			ft_putstr_fd("cd: HOME not set\n", 2);
		return (path);
	}
	if (ft_strcmp(cmd->params[1], "-") == 0)
	{
		path = retrieve_env_path(cmd, envp, "OLDPWD");
		if (!path)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (path);
	}
	return ((char *)cmd->params[1]);
}

void	ft_setenv(t_ast *cmd_path)
{
	size_t	new_size;
	char	*new_path;
	char	*old_pwd;

	if (cmd_path->params[1])
	{
		old_pwd = getenv("PWD");
		if (!old_pwd)
			return ;
		new_size = strlen(old_pwd) + 1 + strlen(cmd_path->params[1]) + 1;
		new_path = malloc(new_size);
		if (!new_path)
			return ;
		snprintf(new_path, new_size, "%s/%s", old_pwd, cmd_path->params[1]);
		setenv("PWD", new_path, 1);
		free(new_path);
	}
}
