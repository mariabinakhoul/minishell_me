/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:59:06 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 17:28:44 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	ft_cd(t_ast *cmd, char **envp)
{
	char	*path;
	char	*old_pwd;

	if (handle_cd_arguments(cmd, envp, &path) != 0)
		return (1);
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
	ft_setenv (cmd);
	free(old_pwd);
	return (0);
}
