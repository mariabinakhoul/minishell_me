/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:15:43 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/23 11:13:21 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	replace_env_node_value(t_env *node, char **old_kv, char **new_kv)
{
	char	*tmp;
	char	*new_str;

	tmp = ft_strjoin(old_kv[0], "=");
	new_str = ft_strjoin(tmp, new_kv[1]);
	free(tmp);
	free(node->data);
	node->data = new_str;
	free_2d(old_kv);
	free_2d(new_kv);
}

void	update_value(t_env *head, char *args)
{
	t_env	*temp;
	char	**value;
	char	**new;

	temp = head;
	value = ft_split(temp->data, '=');
	new = ft_split(args, '=');
	while (temp && ft_strncmp(value[0], new[0], ft_strlen(value[0])) != 0)
	{
		free_2d(value);
		temp = temp->next;
		if (temp)
			value = ft_split(temp->data, '=');
	}
	if (!new[1])
	{
		free_2d(value);
		free_2d(new);
		return ;
	}
	replace_env_node_value(temp, value, new);
}

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
