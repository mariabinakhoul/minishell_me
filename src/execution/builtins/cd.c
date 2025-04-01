/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/01 12:40:52 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char *retrieve_env_path(t_ast *cmd, char **envp, char *key, const char *error_msg, bool print)
{
    char *path;
    int i = 0;

    if (!cmd || !envp || !key)
        return NULL;
    printf(" hello :  %s\n", envp[i]);
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

// static char *get_home_or_oldpwd(t_ast *cmd, char **envp)
// {
//     if (!cmd->params[1])
//         return retrieve_env_path(cmd, envp, "HOME", "cd: HOME not set", false);

//     if (ft_strcmp(cmd->params[1], "-") == 0)
//         return retrieve_env_path(cmd, envp, "OLDPWD", "cd: OLDPWD not set", true);
//     // if (ft_strcmp(cmd->params[1], "--") == 0)
//     // {
//     //     ft_cd(cmd,envp);
//     //     printf("%s", ft_get_oldpwd());
//     // }
//     return (char *)cmd->params[1];
// }

void update_env(t_ast *path)
{
    ft_setenv( path);       // Update PWD
}

void ft_setenv(t_ast *cmd_path)
{
    // int i = 0;
    // char *new_dir = strcat("/", dir);
    // char *env = envp[i];
    if (cmd_path->params[1])
    {
        char *path;
        path = getenv("PWD");
        path = strcat(path,"/");
        path = strcat(path,(cmd_path->params[1]));
    }
    // envp[i] = path;
    // while (envp[i])
    // {
    //     printf("%s\n", env);
    //     i++;
    //     env  = envp[i];
    // }
}


void ft_cd(t_ast *cmd, char **envp) {
    char *path = NULL;
    char *old_pwd;

    if (cmd->params) {
        for (int i = 0; cmd->params[i]; i++) {
            printf("[%s] ", cmd->params[i]);
        }
    }
    printf("\n");

        fprintf(stderr, "bash: cd: too many arguments\n");
    if (cmd->params && cmd->params[1] && cmd->params[2]) {
        return;
    }

    // if (cmd->params[1] && strcmp(cmd->params[1], "~") == 0)
    //     cmd->params[1] = NULL;  // Treat `~` as no argument

    // // Handle `cd -`
    // if (cmd->params[1] && ft_strcmp(cmd->params[1], "-") == 0) {
    //     path = retrieve_env_path(cmd, envp, "OLDPWD", "cd: OLDPWD not set", true);
    if (!path)
        return;  // If OLDPWD is not set, return early
    printf("%s\n", path);  // Print the new directory (like Bash)
    // } else {
    //     path = get_home_or_oldpwd(cmd, envp);
    // }
    if (!path) {
        fprintf(stderr, "cd: could not determine target directory\n");
        return;
    }
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd) {
        perror("cd: getcwd");
        return;
    }
    printf("Attempting to change to: %s\n", path);
    if (chdir(path) != 0) {
        perror("cd");
        free(old_pwd);
        return;
    }
    update_env(cmd);
    free(old_pwd);
}


