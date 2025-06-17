/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:08:17 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 17:23:41 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_escaped_dollar(char *arg, int *i, char **result)
{
	if (arg[*i] == '\\' && arg[*i + 1] == '$')
	{
		*result = join_and_free_char(*result, '$');
		*i += 2;
		return (1);
	}
	return (0);
}

char	*expand_argument(char *arg, int quoted, char **env, int last_status)
{
	char		*result;
	int			i;
	t_expand	two_in_one;

	(void)quoted;
	result = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (handle_escaped_dollar(arg, &i, &result))
			continue ;
		if (arg[i] == '$')
		{
			two_in_one.i = &i;
			two_in_one.result = result;
			result = expand_variable(arg, &two_in_one, env, last_status);
		}
		else
		{
			result = expand_home_directory(arg, &i, env, result);
			if (arg[i] != '~')
				result = join_and_free_char(result, arg[i++]);
		}
	}
	return (result);
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
