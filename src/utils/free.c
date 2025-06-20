/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:37:37 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/09 01:04:31 by mabi-nak         ###   ########.fr       */
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

void	free_lexer_array(struct s_lexer **lexer)
{
	int	i;

	i = 0;
	if (!lexer)
		return ;
	while (lexer[i])
	{
		if (lexer[i]->t_list)
			free(lexer[i]->t_list);
		free(lexer[i]);
		i++;
	}
	free(lexer);
}

void	free_ast(t_ast *node)
{
	int	i;

	i = 0;
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
	if (node->heredoc_delim)
		free(node->heredoc_delim);
	if (node->params)
	{
		while (node->params[i])
			free(node->params[i++]);
		free(node->params);
	}
	if (node->lexer)
		free_lexer_array(node->lexer);
	free(node);
}

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
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->data)
			free(temp->data);
		free(temp);
	}
}
