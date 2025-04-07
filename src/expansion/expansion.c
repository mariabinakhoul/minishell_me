/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:08:17 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/07 21:25:16 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_argument(char *arg, int quoted, char **env, int last_status)
{
	char	*result;
	int		i;
	int		start;

	start = 0;
	result = ft_strdup("");
	i = 0;
	if (quoted == 1)
		return (ft_strdup(arg));
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			if (arg[i + 1] == '?')
			{
				result = join_and_free(result, ft_itoa(last_status));
				i += 2;
			}
			else if (ft_isalpha(arg[i + 1]) || arg[i + 1] == '_')
			{
				start = ++i;
				// char	c = arg[i];
				while (ft_isalnum(arg[i]) || arg[i] == '_')
					i++;
				char	*varname = ft_substr (arg, start, i - start);
				char	*value = get_env_value (varname, env);
				result = join_and_free (result, value ? value : "");
				free (varname);
			}
			else
				result = join_and_free_char(result, arg[i++]);
		}
		else if (i == 0 && arg[i] == '~')
		{
			char *home = get_env_value("HOME", env);
			result = join_and_free(result, home ? home : "");
			i++;
		}
		else
			result = join_and_free_char(result, arg[i++]);
	}
	return result;
}

int cmd_node_param_count(char **params)
{
	int i = 0;
	while (params[i])
		i++;
	return i;
}


void expand_command_node(t_ast *cmd, char **env, int last_status)
{
    int i;
    char *expanded;
    
    i = 0;
    expanded = NULL;
	if (cmd->params)
		cmd->params[cmd_node_param_count(cmd->params)] = NULL;
    while(cmd->params && cmd->params[i])
    {
        expanded = expand_argument(cmd->params[i], 0, env, last_status);
        free(cmd->params[i]);
        cmd->params[i] = expanded;
        i++;
    }
    if (cmd->in_file)
    {
        expanded = expand_argument(cmd->in_file, 0 , env, last_status);
        free(cmd->in_file);
        cmd->in_file = expanded;
    }
    if (cmd->out_file)
    {
        expanded = expand_argument(cmd->out_file, 0, env, last_status);
        free(cmd->out_file);
        cmd->out_file = expanded;
    }
}

void expand_tree(t_ast *node, char **env, int last_status)
{
    if (!node)
        return;
    if (node->type == CMD)
        expand_command_node(node, env, last_status);
    expand_tree(node->left, env, last_status);
    expand_tree(node->right, env, last_status);
}
