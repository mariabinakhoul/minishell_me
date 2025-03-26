/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/26 09:39:04 by nhaber           ###   ########.fr       */
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

void update_env(const char *new_path) {
    char *oldpwd = getenv("PWD");
    if (oldpwd) {
        setenv("OLDPWD", oldpwd, 1);  // Update OLDPWD
    }
    setenv("PWD", new_path, 1);       // Update PWD
}

int ft_setenv(const char *name,const char *path,int overwrite)
{
    if (overwrite != 0)
    {

    }
    return (-1);
}


// void ft_cd(t_ast *cmd, char ***envp_ptr)
// {
//     char *path;
//     char *old_pwd;
//     char **envp = *envp_ptr;

// 	printf("\n=== FT_CD ===\n");
//     printf("Params: ");
//     if (cmd->params) {
//         for (int i = 0; cmd->params[i]; i++) {
//             printf("[%s] ", cmd->params[i]);
//         }
//     }
//     printf("\n");
//     if (!cmd || !cmd->params)
// 	{
// 		printf("Error: Null command or params\n");
//         return;
// 	}
// 	char *target = cmd->params[1] ? cmd->params[1] : getenv("HOME");
//     if (!target) {
//         printf("Error: No directory specified and HOME not set\n");
//         return;
//     }
// 	printf("Attempting to change to: %s\n", target);
//     if (chdir(target) != 0) {
//         perror("cd");
//     }
//     if (cmd->params[1] && cmd->params[2])
//     {
//         fprintf(stderr, "bash: cd: too many arguments\n");
//         return;
//     }

//     path = get_home_or_oldpwd(cmd, envp);
//     if (!path)
//         return;

//     old_pwd = getcwd(NULL, 0);
//     if (!old_pwd)
//     {
//         perror("cd: getcwd");
//         return;
//     }

//     if (chdir(path) == -1)
//     {
//         perror("cd");
//         free(old_pwd);
//         return;
//     }

//     update_environment(cmd, envp_ptr, old_pwd);
// }

void ft_cd(t_ast *cmd, char **envp_ptr) {
    char *path;
    const char *old_pwd;
    char **envp = envp_ptr;
    printf("TEST123  :  %s",*envp_ptr);
    printf("\n=== FT_CD ===\n");
    printf("Param`s: ");
    if (cmd->params) {
        for (int i = 0; cmd->params[i]; i++) {
            printf("[%s] ", cmd->params[i]);
        }
    }
    printf("\n");
    // Check for too many arguments
    if (cmd->params && cmd->params[1] && cmd->params[2]) {
        fprintf(stderr, "bash: cd: too many arguments\n");
        return;
    }

    // Get the target directory
    // printf("TEST  :  %s",*envp);
    path = get_home_or_oldpwd(cmd, envp);
    if (!path) {
        fprintf(stderr, "cd: could not determine target directory\n");
        return;
    }

    // Get current working directory before changing
    old_pwd = getcwd(NULL, 0);
    if (!old_pwd) {
        perror("cd: getcwd");
        return;
    }

    // Attempt to change directory
    printf("Attempting to change to: %s\n", path);
    if (chdir(path) != 0) {
        printf("hello1");
        perror("cd");
        free(old_pwd);
        return;
    }
    // printf("hello2\n");
    printf("%s\n",old_pwd);
    // Update environment variables
    update_env(old_pwd);
    free(old_pwd);
}
