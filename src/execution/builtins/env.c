/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/06 22:11:20 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

t_env *clone_env(char **envp)
{
    t_env *head = NULL;
    t_env *new_node = NULL;
    t_env *last = NULL;

    while (*envp)
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return NULL; // handle error properly in real code
        new_node->data = strdup(*envp); // clone "KEY=VALUE"
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            last->next = new_node;
        last = new_node;
        envp++;
    }
    return head;
}


void ft_env(char **envp)
{
    t_env *env = NULL;

    env = clone_env(envp);

    t_env *tmp = env;
    while (tmp)
    {
        printf("%s\n", tmp->data);
        tmp = tmp->next;
    }
}