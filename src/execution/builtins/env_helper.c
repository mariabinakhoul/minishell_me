/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 21:15:43 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 11:11:13 by nhaber           ###   ########.fr       */
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

void	update_value(t_env *head, char *arg)
{
	t_env	*tmp;
	int		len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	tmp = head;
	while (tmp)
	{
		if (ft_strncmp(tmp->data, arg, len) == 0 && tmp->data[len] == '=')
		{
			free(tmp->data);
			tmp->data = ft_strdup(arg);
			return;
		}
		tmp = tmp->next;
	}
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
