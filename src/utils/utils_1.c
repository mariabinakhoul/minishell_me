/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:25:42 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/12 09:57:50 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	**safe_expand_array(void **ptr, size_t old_count, size_t new_count)
{
	void	**new_ptr;
	size_t	i;

	i = 0;
	new_ptr = malloc(sizeof(void *) * new_count);
	if (!new_ptr)
		return (NULL);
	while (i < old_count)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	i = old_count;
	while (i < new_count)
	{
		new_ptr[i] = NULL;
		i++;
	}
	free(ptr);
	return (new_ptr);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->params)
		free(node->params);
	free(node);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
