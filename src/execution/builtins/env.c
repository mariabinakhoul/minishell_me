/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/08 22:35:14 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/minishell.h"

t_env	*clone_env(char **envp)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*last;

	head = NULL;
	new_node = NULL;
	last = NULL;
	while (*envp)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->data = strdup(*envp);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
			last->next = new_node;
		last = new_node;
		envp++;
	}
	return (head);
}


void	ft_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;

	env = NULL;
	env = clone_env(envp);
	tmp = env;
	while (tmp)
	{
		printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
