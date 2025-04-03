/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:35:53 by mabi-nak          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/03 14:40:28 by mabi-nak         ###   ########.fr       */
=======
/*   Updated: 2025/04/02 00:03:20 by nhaber           ###   ########.fr       */
>>>>>>> refs/remotes/origin/main
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

// retrieve the value of an environment variable, 
static char *retrieve_env_path(t_ast *cmd, char **envp, char *key, const char *error_msg, bool print)
{
    char *path;
    int i = 0;

    if (!cmd || !envp || !key)
        return NULL;
    // printf(" hello :  %s\n", envp[i]);
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
    {
        return retrieve_env_path(cmd, envp, "OLDPWD", "cd: OLDPWD not set", true);
        // update_env(cmd);
    }
    // if (ft_strcmp(cmd->params[1], "--") == 0)
    // {
    //     ft_cd(cmd,envp);
    //     printf("%s", ft_get_oldpwd());
    // }
    return (char *)cmd->params[1];
}

void update_env(t_ast *path)
{
    ft_setenv( path);       // Update PWD
}

// void ft_setenv(t_ast *cmd_path)
// {
//     // int i = 0;
//     // char *new_dir = strcat("/", dir);
//     // char *env = envp[i];
//     if (strcmp(cmd_path->params[1], "..") == 0)
//         return ;
//     if (cmd_path->params[1])
//     {
//         char *path;
//         path = getenv("PWD");
//         path = strcat(path,"/");
//         path = strcat(path,(cmd_path->params[1]));
//     }
//     // envp[i] = path;
//     // while (envp[i])
//     // {
//     //     printf("%s\n", env);
//     //     i++;
//     //     env  = envp[i];
//     // }
// }

/*
    *Both setenvs are not working but the one below is completely wrong.

    *if this is fixed the "cd -" case is automatically fixed.
    
    *Dont fix it so git does not cause conflict!!!!!! (If Maria is reading this). 
 */

void ft_setenv(t_ast *cmd_path)
{
    if (cmd_path->params[1])
    {
        char *old_pwd = getenv("PWD");
        if (!old_pwd)
            return;  // or handle error
        
        size_t new_size = strlen(old_pwd) + 1 /* for "/" */ + strlen(cmd_path->params[1]) + 1;
        char *new_path = malloc(new_size);
        if (!new_path)
            return;  // or handle malloc failure

        snprintf(new_path, new_size, "%s/%s", old_pwd, cmd_path->params[1]);
        // Now update your environment variable or internal PWD accordingly,
        // for example with setenv("PWD", new_path, 1);
        setenv("PWD", new_path, 1);
        free(new_path);
    }
}


void ft_cd(t_ast *cmd, char **envp) {
    char *path = NULL;
    char *old_pwd;

    if (cmd->params && cmd->params[1] && cmd->params[2]) {
        fprintf(stderr, "bash: cd: too many arguments\n");
        return;
    }

    if (cmd->params[1] && strcmp(cmd->params[1], "~") == 0)
        cmd->params[1] = NULL;

    //  `cd -`
    if (cmd->params[1] && ft_strcmp(cmd->params[1], "-") == 0) {
        path = retrieve_env_path(cmd, envp, "OLDPWD", "cd: OLDPWD not set", true);
    if (!path) 
        return; 
    printf("%s\n", path);  // Print the new directory (like Bash)
    } else {
        path = get_home_or_oldpwd(cmd, envp);
    }

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

    update_env(cmd);  // Ensure OLDPWD and PWD are updated
    free(old_pwd);
}