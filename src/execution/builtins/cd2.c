/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:59:06 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 16:26:26 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*retrieve_env_path(t_ast *cmd, char **envp, char *key)
{
	int		i;

	i = 0;
	if (!cmd || !envp || !key)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
			&& envp[i][ft_strlen(key)] == '=')
			return (&envp[i][ft_strlen(key) + 1]);
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

int	handle_cd_arguments(t_ast *cmd, char **envp, char **path)
{
	if (cmd->params && cmd->params[1] && cmd->params[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->params[1] && ft_strcmp(cmd->params[1], "~") == 0)
		cmd->params[1] = NULL;
	*path = get_home_or_oldpwd(cmd, envp);
	if (!path)
	{
		ft_putstr_fd("cd: could not determine target directory\n", 2);
		return (1);
	}
	return (0);
}

int	ft_cd(t_ast *cmd, char ***envp)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (handle_cd_arguments(cmd, *envp, &path) != 0)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("cd: getcwd"), 1);
	if (path == NULL)
		return(free(old_pwd),1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (free(old_pwd), 1);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd: getcwd (after chdir)");
		return (free(old_pwd), 1);
	}
	*envp = update_env_var_array(*envp, "OLDPWD", old_pwd);
	*envp = update_env_var_array(*envp, "PWD", new_pwd);
	return (free(old_pwd), free(new_pwd), 0);
}
