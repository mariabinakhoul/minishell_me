/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 16:00:29 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	update_existing_env_var(char **envp, char *key, char *new_var)
{
	int		len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

char	**update_env_var_array(char **envp, char *key, char *value)
{
	int		i;
	int		len;
	char	*new_var;
	char	**new_envp;

	len = ft_strlen(key);
	new_var = malloc(len + ft_strlen(value) + 2);
	if (!new_var)
		return (envp);
	ft_strcpy(new_var, key);
	ft_strcat(new_var, "=");
	ft_strcat(new_var, value);
	if (update_existing_env_var(envp, key, new_var))
		return (envp);
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (free(new_var), envp);
	new_envp[i + 1] = NULL;
	new_envp[i] = new_var;
	while (--i >= 0)
		new_envp[i] = envp[i];
	return (free(envp), new_envp);
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
		new_size = ft_strlen(old_pwd) + 1 + ft_strlen(cmd_path->params[1]) + 1;
		new_path = malloc(new_size);
		if (!new_path)
			return ;
		ft_putstr_fd(old_pwd, 2);
		ft_putstr_fd("/", 2);
		ft_putstr_fd(cmd_path->params[1], 2);
		setenv("PWD", new_path, 1);
		free(new_path);
	}
}
