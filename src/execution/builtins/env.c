/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/03/28 21:26:35 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

void clone_env(char **envp)
{
    char *env;
    
    int i = 0;
    env = envp[i];
    while (envp[i])
    {
        
    }
}

void ft_env(char **envp)
{
    int i = 0;

    char *env = envp[i];
    while (envp[i])
    {
        i++;
        printf("%s\n" ,env);
        env = envp[i];
    }
}