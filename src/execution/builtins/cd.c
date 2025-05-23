/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/19 19:29:18 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*retrieve_env_path(t_ast *cmd,
		char **envp, char *key, const char *error_msg, bool print)
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
			if (print)
				printf("%s\n", path);
			return (path);
		}
		i++;
	}
	if (error_msg)
		fprintf(stderr, "%s\n", error_msg);
	return (NULL);
}

static char	*get_home_or_oldpwd(t_ast *cmd, char **envp)
{
	if (!cmd->params[1])
		return (retrieve_env_path(cmd, envp, "HOME",
				"cd: HOME not set", false));
	if (ft_strcmp(cmd->params[1], "-") == 0)
		return (retrieve_env_path(cmd, envp, "OLDPWD",
				"cd: OLDPWD not set", true));
	return ((char *)cmd->params[1]);
}

void	update_env(t_ast *path)
{
	ft_setenv (path);
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

int	ft_cd(t_ast *cmd, char **envp)
{
	char	*path;
	char	*old_pwd;

	if (cmd->params && cmd->params[1] && cmd->params[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->params[1] && strcmp(cmd->params[1], "~") == 0)
		cmd->params[1] = NULL;
	path = get_home_or_oldpwd(cmd, envp);
	if (!path)
	{
		ft_putstr_fd("cd: could not determine target directory\n", 2);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	update_env(cmd);
	free(old_pwd);
	return (0);
}
