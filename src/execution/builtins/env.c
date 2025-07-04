/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/25 15:54:55 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*add_new_node(t_env *head, char *arg)
{
	t_env	*new_node;
	t_env	*tmp;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (head);
	new_node->data = ft_strdup(arg);
	new_node->next = NULL;
	if (!head)
		return (new_node);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (head);
}

t_env	*create_node(t_env *head, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!args_found(head, args[i]))
			head = add_new_node(head, args[i]);
		else
			update_value(head, args[i]);
		i++;
	}
	return (head);
}

int	update_shlvl_if_match(t_env *node)
{
	char	**split;
	int		shlvl;
	char	*new_value;
	char	*new_entry;

	if (ft_strncmp(node->data, "SHLVL=", 6) != 0)
		return (0);
	split = ft_split(node->data, '=');
	if (!split || !split[1])
		return (0);
	shlvl = ft_atoi(split[1]);
	new_value = ft_itoa(shlvl + 1);
	new_entry = ft_strjoin("SHLVL=", new_value);
	free(node->data);
	node->data = new_entry;
	free_2d(split);
	free(new_value);
	return (1);
}

void	increment_shlvl(t_env *env_list)
{
	t_env	*temp;
	t_env	*new_node;

	temp = env_list;
	while (temp)
	{
		if (update_shlvl_if_match(temp))
			return ;
		temp = temp->next;
	}
	temp = env_list;
	while (temp && temp->next)
		temp = temp->next;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->data = ft_strdup("SHLVL=1");
	new_node->next = NULL;
	if (temp)
		temp->next = new_node;
}

char	**set_env(char **envp)
{
	t_env	*env_list;
	char	**new_env;

	env_list = convert_to_list(envp);
	increment_shlvl(env_list);
	new_env = convert_to_2d(env_list);
	free_list(env_list);
	return (new_env);
}
