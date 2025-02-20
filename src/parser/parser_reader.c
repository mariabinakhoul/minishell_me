/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:30:30 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/20 10:59:01 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ast	*new_ast_node(t_token type, char *value)
{
	t_ast	*node;

	node = malloc (sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	find_last_pipe(t_chain	*tokens)
{
	int	i;
	int	last_pipe;

	i = 0;
	last_pipe = -1;
	while (tokens[i].type != TYPE_NP)
	{
		if (tokens[i].type == TYPE_PIPE)
			last_pipe = i;
		i++;
	}
	return (last_pipe);
}

t_ast split_at_last_pipe(t_chain *tokens)
{
	
}

t_ast	*parser_filler(t_token)
{
	
}