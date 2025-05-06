/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:37:37 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/06 09:17:48 by nhaber           ###   ########.fr       */
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
    if (ast != NULL)
    {
        free_ast(ast->left);
        free_ast(ast->right);
    }
    free(ast);
}


void free_2d(char **str)
{
    int i;

    i = 0;
    if (!str)
        return ;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

void free_list(t_env *head)
{
    if (head != NULL)
        free_list(head->next);
    free (head);
}