/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:08:17 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/04 00:30:50 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_argument(char *arg, int quoted, char **env, int exit_code)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	if (!arg) {
        fprintf(stderr, "Error: Null argument passed to expand_argument.\n");
        return NULL;
    }
	// if (quoted == 1)
		// return (ft_strdup(arg));
	while (arg[i])
	{
		if (arg[i] == '\\' && arg[i+1] == '$')
		{
			result = join_and_free_char(result, '$');
			i += 2;
			continue ;
		}
		if (arg[i] == '$')
			result = expand_variable(arg, &i, env, exit_code, result);
		else
		{
			result = expand_home_directory(arg, &i, env, result);
			if (arg[i] != '~')
				result = join_and_free_char(result, arg[i++]);
		}
	}
	return (result);
}

int	cmd_node_param_count(char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	return (i);
}

void	expand_file_argument(char **file_arg, char **env, int exit_code)
{
	char	*expanded;

	if (*file_arg)
	{
		expanded = expand_argument(*file_arg, 0, env, exit_code);
		free(*file_arg);
		*file_arg = expanded;
	}
}

void	expand_command_node(t_ast *cmd, char **env, int last_status)
{
	int		i;
	char	*expanded;
	int		quote;

	i = 0;
	expanded = NULL;
	// printf("expand_command_node called for params: ");
	// for (int j = 0; cmd->params && cmd->params[j]; j++)
	// {
	// 	printf("%s ", cmd->params[j]);
	// }
	// printf("\n");
	if (cmd->params)
		cmd->params[cmd_node_param_count(cmd->params)] = NULL;
	while (cmd->params && cmd->params[i])
	{
		quote = 0;
		if (cmd->lexer && cmd->lexer[i])
			quote = cmd->lexer[i]->count;
		expanded = expand_argument(cmd->params[i], quote, env, last_status);
		free(cmd->params[i]);
		cmd->params[i] = expanded;
		i++;
	}
	expand_file_argument(&cmd->in_file, env, last_status);
	expand_file_argument(&cmd->out_file, env, last_status);
}

void	expand_tree(t_ast *node, char **env, int exit_code)
{
	if (!node)
		return ;
	if (node->type == CMD)
		expand_command_node(node, env, exit_code);
	expand_tree(node->left, env, exit_code);
	expand_tree(node->right, env, exit_code);
}
