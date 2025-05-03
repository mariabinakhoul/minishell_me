/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:37:37 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/04 00:52:41 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_lexer_nodes(t_chain *head)
{
	t_chain	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

void free_ast(t_ast *ast)
{
    if (!ast)
        return;
    free_ast(ast->left);
    free_ast(ast->right);

    // Free node-specific fields
    free(ast->value);
    if (ast->params)
    {
        for (int i = 0; ast->params[i]; i++)
            free(ast->params[i]);
        free(ast->params);
    }

    // Free lexer-related structures if they exist
    if (ast->lexer)
    {
        for (int i = 0; ast->lexer[i]; i++)
            free(ast->lexer[i]);
        free(ast->lexer);
    }

    // Free other members of the AST node
    free(ast);
}
