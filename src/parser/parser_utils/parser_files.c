/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:43:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/10 21:40:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	redirect_to_in(t_ast_utils **util)
{
	int	fd;

	if (!(*util)->in)
		return ;
	fd = open ((*util)->in, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening input file");
		(*util)->exit = 1;
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(fd);
		return ;
	}
	close (fd);
}

void	redirect_to_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error opening file for output redirection");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return ;
	}
	close(fd);
}

void	init_parser(t_lexer **lex, t_syntax_tree **tree)
{
	if (!lex || !*lex || !tree || !*tree)
		return ;

	(*tree)->branch = parser_build_tree(lex, (*lex)->t_list);
	if (!(*tree)->branch)
		return ;
	if ((*tree)->branch->params)
		expand_tree((*tree)->branch);
}

void	process_tree_node(t_ast *node)
{
	if (node->params && node->params[0])
	{
		node->tree_link = ft_calloc(1, sizeof(t_syntax_tree));
		init_parser(node->lexer, &node->tree_link);
		if (!(node->tree_link->branch->out_file) && node->out_file)
			node->tree_link->branch->out_file = ft_strdup(node->out_file);
		if (!node->tree_link->branch->in_file && node->in_file)
		{
			node->tree_link->branch->in_file = ft_strdup(node->in_file);
			node->tree_link->branch->heredoc = node->heredoc;
		}
	}
}

void	expand_tree(t_ast *node)
{
	if (!node)
		return ;
	process_tree_node(node);
	expand_tree(node->left);
	expand_tree(node->right);
}


// void	parser_first_tree(t_ast *node)
// {
// 	if (!node)
// 		return ;
// 	if (node ->params && node->params[0])
// 	{
// 		node->tree_link = ft_calloc(1, sizeof(t_syntax_tree));
// 		if (!node->tree_link)
// 			return ;
// 	}
// }
