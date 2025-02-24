/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:30:30 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/22 08:36:00 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// in this file we're working on the main parser that will help us to create the tree
//ast as abstract syntax tree 

//it creates like a new node of the ast
t_ast	*new_ast_node(t_ast_type type, char *value)
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
// t_ast *create_command_node(t_chain *tokens)
// {
// 	t_ast *cmd_node;
// 	char **args;

// 	if (!tokens)
// 		return (NULL);
// 	args = get_args_from_the_tokens(tokens);
// 	if (!args)
// 		return (NULL);
// 	cmd_node = new_ast_node(TYPE_WORD, args[0]);
// 	return (cmd_node);
// }

// t_ast	*split_at_last_pipe(t_chain *tokens)
// {
// 	int	last_pipe;
// 	t_chain *temp;
// 	t_ast *root;

// 	last_pipe = find_last_pipe(tokens);
// 	if (!(last_pipe == -1))
// 		return (create_command_node(tokens));
// 	temp = tokens;
// 	for ( int i = 0; i < last_pipe; i++)
// 		temp = temp->next;
// 	root = new_ast_node(TYPE_PIPE, "|");
// 	root->left = split_at_last_pipe(tokens);
// 	root->right = split_at_last_pipe(temp->next);
// 	return (root);
// }


