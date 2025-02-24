/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:51:33 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/24 18:36:12 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (NULL);
	node->left = left;
	node->right = right;
	if (type == TYPE_PIPE)
	{
		node->type = TYPE_PIPE;
		node->params = ft_split(PIPE, ' ');
	}
	return (node);
}

void	make_cmd_ast(t_ast *node, t_ast *util)
{
	node->type = CMD;
	node->in_file = util->in_file;
	node->out_file = util->out_file;
	node->exit = util->exit;
	node->heredoc = util->heredoc;
	node->left = NULL;
	node->right = NULL;
	if (util->params)
		node->params = util->params;
}

void	parse_heredoc(t_token_b *token, t_ast_utils **util)
{
	if (token->type == TYPE_HEREDOC)
	{
		if (token->extend == -5)
			(*util)->heredoc = 5;
		else
			(*util)->heredoc = 1;
	}
}

t_ast	*generate_simple_cmd(t_ast_utils *util)
{
	t_ast	*node;
	char	**args;

	node = ft_calloc(1, sizeof(t_ast));
	args = NULL;
	if (!node || !util->params)
		return (NULL);
	if (ft_strcmp(util->params, "echo") == 0 && util->echo == 0)
	{
		args = malloc(3 * sizeof(char *));
		if (!args)
			return (NULL);
		args[0] = ft_strdup("echo");
		args[1] = ft_substr(util->params, 5, ft_strlen(util->params));
		args[2] = NULL;
	}
	else
		args = ft_split(util->params, ' ');
	node->params = args;
	make_cmd_ast(&node, &util);
	return (node);
}
