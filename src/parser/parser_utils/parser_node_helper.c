/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:51:33 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/10 21:28:13 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"



//initializes a cmd ast node with values from a node.
//*node is the node to be initialized and *util contains the values
//it sets the type as CMD and assigns the inputs and outputs etc.
//also left and right side must be NULL and if params exist they copyt it.
void	make_cmd_ast(t_ast *node, t_ast *util)
{
	node->type = CMD;
	node->in_file = util->in_file;
	node->exit = util->exit;
	node->out_file = util->out_file;
	node->heredoc = util->heredoc;
	node->left = NULL;
	node->right = NULL;
	if (util->params)
		node->params = util->params;
}

t_ast_utils	*make_util_ast(t_ast_utils **util)
{
	(*util) = ft_calloc(1, sizeof(t_ast_utils));
	(*util)->in = NULL;
	(*util)->out = NULL;
	(*util)->exit = 0;
	(*util)->node = NULL;
	(*util)->right = NULL;
	(*util)->echo = 0;
	(*util)->params = NULL;
	return (*util);
}

//creates a simple cmd ast node
//*util containing command parameters and metdata
//it allocates memory for the new ast node and it init depending on util
//it manually constructs the arg array. Otherwise, it splits the params
//it calls make_cmd_ast to set up the node
t_ast	*generate_echo_cmd(t_ast_utils *util)
{
	t_ast	*node;
	char	**args;

	node = ft_calloc(1, sizeof(t_ast));
	args = NULL;
	printf("test1\n");
	// if (!node || !util || !util->params)
	// {
	// 	printf("Error: Failed to allocae memory for echo cmd\n");
	// 	return (NULL);
	// }
	printf("Generating echo cmd with params: %s\n", util->params);
	if (util->params != NULL)
	{
		if (ft_strcmp(util->params, "echo") == 0 && util->echo == 0)
	{
		printf("kaakl\n");
		args = malloc(3 * sizeof(char *));
		if (!args)
		{
			printf("Error: Failed to split params\n");
			free(node);
			return (NULL);
		}
		args[0] = ft_strdup("echo");
		args[1] = ft_substr(util->params, 5, ft_strlen(util->params));
		args[2] = NULL;
	}	
	}
	else
		args = ft_split(util->params, ' ');
	node->params = args;
	make_cmd_ast(node, (t_ast *)util);
	return (node);
}

static int	extra_addition(char *params, size_t *len_params)
{
	if (params)
	{
		*len_params = ft_strlen(params);
		return (2);
	}
	else
	{
		*len_params = 0;
		return (1);
	}
}

char	*create_cmd_params(char *value, char *params)
{
	char	*new_param;
	size_t	len_v;
	size_t	len_params;
	int		add;

	len_v = ft_strlen(value);
	add = extra_addition(params, &len_params);
	new_param = malloc(len_params + len_v + add);
	if (!new_param)
		return (NULL);
	if (params)
	{
		ft_strcpy(new_param, params);
		ft_strcat(new_param, " ");
		ft_strcat(new_param, value);
		free(params);
	}
	else
		ft_strcpy(new_param, value);
	return (new_param);
}
