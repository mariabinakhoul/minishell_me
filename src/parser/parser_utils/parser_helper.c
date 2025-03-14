/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 05:49:48 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/08 01:48:51 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//create a separator node (ast) assigning the type if it's a pipe else ma
//ela aaze and assigning the right and the left
//it allocates and initializ a new ast that represents the separato only
//and splits them into arguments (it returns a pointer of
//the new ast_node or NULL if it fails)


t_ast	*make_ast_separator(t_ast *left, t_ast *right, int type)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
	{
		printf("Error: Failed to allocate memory for seperator node\n");
		return (NULL);
	}
	node->left = left;
	node->right = right;
	if (type == TYPE_PIPE)
	{
		node->type = PIPE;
		node->params = ft_split((char *)PIPE, ' ');
		if (!node->params)
		{
			printf("Error: Failed to split pipe param\n");
			free(node);
			return (NULL);
		}
	}
	return (node);
}
