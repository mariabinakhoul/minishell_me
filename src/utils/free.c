/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:37:37 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/21 22:26:04 by mabi-nak         ###   ########.fr       */
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

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);

	 if (node->value)
        free(node->value);
    
    if (node->in_file)
        free(node->in_file);
    if (node->out_file)
        free(node->out_file);
    // if (node->heredoc_delim)
    //     free(node->heredoc_delim);
    if (node->params)
    {
        for (int i = 0; node->params[i]; i++)
            free(node->params[i]);
        free(node->params);
    }

    // Free any lexer or other allocated fields similarly

    free(node);
}

// void	free_ast(t_ast *ast)
// {
// 	if (ast != NULL)
// 	{
// 		free_ast(ast->left);
// 		free_ast(ast->right);
// 	}
// 	free(ast);
// }

void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_list(t_env *head)
{
	if (head != NULL)
		free_list(head->next);
	free (head);
}
