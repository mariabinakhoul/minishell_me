/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 21:26:34 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/16 16:23:55 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (joined);
}

t_env	*create_node(t_env *head, char **args)
{
	t_env	*new_node;
	t_env	*tmp;

	if (args_found(head, args) == 0)
	{
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
	}
	else
		update_value(head, args);
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
		if (ft_strchr(environment[i], '='))
			printf("%s\n", environment[i]);
		i++;
	}
	free_2d(environment);
}
