/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:36:28 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/18 15:25:03 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_node_to_list1(t_env **head, t_env **curr, t_env *new_node)
{
	if (!*head)
	{
		*head = new_node;
		*curr = *head;
	}
	else
	{
		(*curr)->next = new_node;
		*curr = new_node;
	}
}

t_env	*convert_to_list(char **envp)
{
	t_env	*head;
	t_env	*curr;
	t_env	*new_node;
	int		i;

	i = 0;
	head = NULL;
	curr = NULL;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->data = ft_strdup(envp[i]);
		new_node->next = NULL;
		add_node_to_list1(&head, &curr, new_node);
		i++;
	}
	return (head);
}

char	**convert_to_2d(t_env *head)
{
	int		count;
	t_env	*tmp;
	int		i;
	char	**converted_env;

	i = 0;
	count = 0;
	tmp = head;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	converted_env = malloc((count + 1) * sizeof(char *));
	if (!converted_env)
		return (NULL);
	while (head)
	{
		converted_env[i] = ft_strdup(head->data);
		i++;
		head = head->next;
	}
	converted_env[i] = NULL;
	return (converted_env);
}

int	match_and_cleanup(t_env *node, char **new_arr)
{
	char	**value;

	value = ft_split(node->data, '=');
	if (!value)
		return (0);
	if (ft_strncmp(value[0], new_arr[0], ft_strlen(value[0])) == 0)
	{
		free_2d(value);
		free_2d(new_arr);
		return (1);
	}
	free_2d(value);
	return (0);
}

int	args_found(t_env *head, char **args)
{
	t_env	*temp;
	char	**new;

	new = ft_split(args[1], '=');
	if (!new)
		return (0);
	temp = head;
	while (temp)
	{
		if (match_and_cleanup(temp, new))
			return (1);
		temp = temp->next;
	}
	free_2d(new);
	return (0);
}
