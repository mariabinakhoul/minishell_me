/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:25 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 16:15:05 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_redirection(t_chain **tokens, t_ast *cmd_node, char **env)
{
	t_chain	*token;
	t_chain	*next;
	char	*filename;

	token = *tokens;
	if (token)
		next = token->next;
	else
		next = NULL;
	if (!token || !next || (next->type != TYPE_WORD
			&& next->type != TYPE_QUOTE))
	{
		ft_putstr_fd("minishell: syntax error: missing file"
			" name after redirection operator.\n", 2);
		if (next)
			*tokens = next->next;
		else
			*tokens = NULL;
		return (1);
	}
	filename = ft_strdup(next->value);
	condition_redirection(cmd_node, token, filename, env);
	*tokens = next->next;
	return (0);
}

int	condition_redirection(t_ast *cmd_node, t_chain *token,
	char *filename, char **env)
{
	if (token->type == TYPE_OUTDIR)
	{
		if (cmd_node->out_file)
			free(cmd_node->out_file);
		cmd_node->out_file = filename;
		cmd_node->append = 0;
	}
	else if (token->type == TYPE_APPEND)
	{
		if (cmd_node->out_file)
			free(cmd_node->out_file);
		cmd_node->out_file = filename;
		cmd_node->append = 1;
	}
	else
		handle_input_redirection(cmd_node, token, filename, env);
	return (0);
}
