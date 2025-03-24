/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/24 22:04:55 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// static char	*retrieve_env_path(t_ast *cmd, char **envp,
// 	char *key, const char *error_msg, bool print)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	if (!cmd || !envp || !key)
// 		return (NULL);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0
// 			&& envp[i][ft_strlen(key)] == '=')
// 		{
// 			path = &envp[i][ft_strlen(key) + 1];
// 			if (print)
// 				printf("%s\n", path);
// 			return (path);
// 		}
// 		i++;
// 	}
// 	if (error_msg)
// 		fprintf(stderr, "%s\n", error_msg);
// 	return (NULL);
// }

// static char	*get_home_or_oldpwd(t_ast *cmd, char **envp)
// {
// 	if (!cmd->params[1])
// 		return (retrieve_env_path(cmd, envp, "HOME",
// 				"cd: HOME not set", false));
// 	if (ft_strcmp(cmd->params[1], "-") == 0)
// 		return (retrieve_env_path(cmd, envp, "OLDPWD",
// 				"cd: OLDPWD not set", true));
// 	if (ft_strcmp(cmd->params[1], "--") == 0)
// 		return (retrieve_env_path(cmd, envp, "OLDPWD",
// 				"cd: OLDPWD not set", false));
// 	return ((char *)cmd->params[1]);
// }

// static void	update_environment(t_ast *cmd, char **envp, char *old_pwd)
// {
// 	char	*new_pwd;
// 	int		i;
// 	(void)cmd;

// 	i = 0;
// 	if (!envp || !old_pwd)
// 		return ;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0 && envp[i][6] == '=')
// 		{
// 			char *tmp =  ft_strjoin("OLDPWD=", old_pwd); 
// 			if (tmp)
// 				envp[i] = (tmp);  // Free only if dynamically allocated
// 			break;
// 		}
// 		i++;
// 	}
// 	free(old_pwd);
// 	new_pwd = getcwd(NULL, 0);
// 	if (!new_pwd)
// 	{
// 		perror("cd: getcwd");
// 		return ;
// 	}
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PWD", 3) == 0 && envp[i][3] == '=')
// 		{
// 			char *tmp = ft_strjoin("PWD=", new_pwd);
// 			if (tmp)
// 			{
// 			// 	printf("Freeing envp1[%d]: %s\n", i, envp[i]);
// 			// 	free(envp[i]);
// 			envp[i] = tmp;

// 		}
// 			// envp[i] = ft_strjoin("PWD=", new_pwd);
// 			break ;
// 		}
// 		i++;
// 	}
// 	free(new_pwd);
// }

// // static void update_environment(t_ast *cmd, char **envp, char *old_pwd)
// // {
// //     char *new_pwd;
// //     int i;
// // 	(void)cmd;

// //     i = 0;
// //     if (!envp || !old_pwd)
// //         return;

// //     // Update OLDPWD in environment
// //     while (envp[i])
// //     {
// //         if (ft_strncmp(envp[i], "OLDPWD", 6) == 0 && envp[i][6] == '=')
// //         {
// //             char *tmp = envp[i];
// //             envp[i] = ft_strjoin("OLDPWD=", old_pwd);
// //             free(tmp);  // Free old dynamically allocated memory
// //             break;
// //         }
// //         i++;
// //     }

// //     new_pwd = getcwd(NULL, 0);
// //     if (!new_pwd)
// //     {
// //         perror("cd: getcwd");
// //         return;
// //     }

// //     // Update PWD in environment
// //     i = 0;
// //     while (envp[i])
// //     {
// //         if (ft_strncmp(envp[i], "PWD", 3) == 0 && envp[i][3] == '=')
// //         {
// //             char *tmp = envp[i];
// //             envp[i] = ft_strjoin("PWD=", new_pwd);
// //             free(tmp);  // Free old dynamically allocated memory
// //             break;
// //         }
// //         i++;
// //     }

// //     free(new_pwd); // Free the dynamically allocated string from getcwd
// // }



// void	ft_cd(t_ast *cmd, char **envp)
// {
// 	char	*path;
// 	char	*old_pwd;

// 	printf("cmd->params[0]: %s, cmd->params[1]: %s\n",
// 		cmd->params[0], cmd->params[1] ? cmd->params[1] : "(null)");
// 	if (!cmd || !cmd->params)
// 		return ;
// 	if (cmd->params[1] && cmd->params[2])
// 	{
// 		fprintf(stderr, "bash: cd too many arguments\n");
// 		return ;
// 	}
// 	path = get_home_or_oldpwd(cmd, envp);
// 	if (!path)
// 		return ;
// 	old_pwd = getcwd(NULL, 0);
// 	if (!old_pwd)
// 	{
// 		perror("cd: getcwd");
// 		return ;
// 	}
// 	if (chdir(path) == -1)
// 	{
// 		perror("cd");
// 		free(old_pwd);
// 		return ;
// 	}
// 	else
// 		update_environment(cmd, envp, old_pwd);
// }


#include "../../../includes/minishell.h"

static char *retrieve_env_path(t_ast *cmd, char **envp, char *key, const char *error_msg, bool print)
{
    char *path;
    int i = 0;

    if (!cmd || !envp || !key)
        return NULL;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0 && envp[i][ft_strlen(key)] == '=')
        {
            path = &envp[i][ft_strlen(key) + 1];
            if (print)
                printf("%s\n", path);
            return path;
        }
        i++;
    }

    if (error_msg)
        fprintf(stderr, "%s\n", error_msg);
    return NULL;
}

static char *get_home_or_oldpwd(t_ast *cmd, char **envp)
{
    if (!cmd->params[1])
        return retrieve_env_path(cmd, envp, "HOME", "cd: HOME not set", false);

    if (ft_strcmp(cmd->params[1], "-") == 0)
        return retrieve_env_path(cmd, envp, "OLDPWD", "cd: OLDPWD not set", true);

    if (ft_strcmp(cmd->params[1], "--") == 0)
        return retrieve_env_path(cmd, envp, "OLDPWD", "cd: OLDPWD not set", false);

    return (char *)cmd->params[1];
}

static void update_environment(t_ast *cmd, char **envp, char *old_pwd)
{
    char *new_pwd;
    int i = 0;
    char *tmp;
	(void)cmd;

    if (!envp || !old_pwd)
        return;

    while (envp[i])
    {
        if (ft_strncmp(envp[i], "OLDPWD", 6) == 0 && envp[i][6] == '=')
        {
            tmp = ft_strjoin("OLDPWD=", old_pwd);
            if (tmp)
            {
                free(envp[i]);  // Free the previous entry before updating
                envp[i] = tmp;
            }
            break;
        }
        i++;
    }

    new_pwd = getcwd(NULL, 0);
    if (!new_pwd)
    {
        perror("cd: getcwd");
        return;
    }

    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], "PWD", 3) == 0 && envp[i][3] == '=')
        {
            tmp = ft_strjoin("PWD=", new_pwd);
            if (tmp)
            {
                free(envp[i]);  // Free the previous entry before updating
                envp[i] = tmp;
            }
            break;
        }
        i++;
    }

    free(new_pwd);
}

void ft_cd(t_ast *cmd, char **envp)
{
    char *path;
    char *old_pwd;

    printf("cmd->params[0]: %s, cmd->params[1]: %s\n",
        cmd->params[0], cmd->params[1] ? cmd->params[1] : "(null)");

    if (!cmd || !cmd->params)
        return;

    if (cmd->params[1] && cmd->params[2])
    {
        fprintf(stderr, "bash: cd: too many arguments\n");
        return;
    }

    path = get_home_or_oldpwd(cmd, envp);
    if (!path)
        return;

    old_pwd = getcwd(NULL, 0);
    if (!old_pwd)
    {
        perror("cd: getcwd");
        return;
    }

    if (chdir(path) == -1)
    {
        perror("cd");
        free(old_pwd);
        return;
    }

    update_environment(cmd, envp, old_pwd);
}

