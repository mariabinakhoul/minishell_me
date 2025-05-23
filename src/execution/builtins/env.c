/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/22 19:58:03 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		if (!head)
		{
			head = new_node;
			curr = head;
		}
		else
		{
			curr->next = new_node;
			curr = new_node;
		}
		i++;
	}
	return (head);
}

void	print_env(t_env *head)
{
	while (head != NULL)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
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
		converted_env[i] = strdup(head->data);
		i++;
		head = head->next;
	}
	converted_env[i] = NULL;
	return (converted_env);
}

void	print2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

t_env	*create_node(t_env *head, char **args)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (head);
	new_node->data = ft_strdup(args[1]);
	new_node->next = NULL;
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

char	**set_env(char **envp)
{
	t_env	*env_list;
	char	**new_env;

	env_list = convert_to_list(envp);
	new_env = convert_to_2d(env_list);
	free_list(env_list);
	return (new_env);
}

void	ft_env(char **envp)
{
	char	**environment;
	int		i;

	i = 0;
	environment = set_env(envp);
	while (environment[i])
	{
		printf("%s\n", environment[i]);
		i++;
	}
	free_2d(environment);
}
