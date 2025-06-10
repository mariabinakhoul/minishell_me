/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_alpha2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:40:52 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/09 16:16:20 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_tokens(t_chain **tokens, t_ast *cmd_node, int *param_count)
{
	while (*tokens && (*tokens)->type != TYPE_PIPE)
	{
		if (((*tokens)->type == TYPE_INDIR) || (*tokens)->type == TYPE_OUTDIR
			|| (*tokens)->type == TYPE_APPEND
			|| (*tokens)->type == TYPE_HEREDOC)
			parse_redirection(tokens, cmd_node);
		else
		{
			if (!(cmd_node->value))
				cmd_node->value = ft_strdup((*tokens)->value);
			expand_params_and_lexer(cmd_node, *tokens, param_count);
			(*param_count)++;
			cmd_node->params[*param_count] = NULL;
			*tokens = (*tokens)->next;
		}
	}
}

t_ast	*parse_command(t_chain **tokens)
{
	t_ast	*cmd_node;
	int		param_count;

	if ((!(*tokens)) || (*tokens)->type == TYPE_PIPE)
		return (NULL);
	cmd_node = malloc(sizeof(t_ast));
	if (!cmd_node)
		return (NULL);
	cmd_node->type = CMD;
	cmd_node->params = NULL;
	cmd_node->value = NULL;
	cmd_node->heredoc_delim = NULL;
	cmd_node->in_file = NULL;
	cmd_node->out_file = NULL;
	cmd_node->append = 0;
	cmd_node->right = NULL;
	cmd_node->left = NULL;
	cmd_node->tree_link = NULL;
	cmd_node->exit = 0;
	cmd_node->lexer = NULL;
	cmd_node->heredoc = 0;
	param_count = 0;
	process_tokens(tokens, cmd_node, &param_count);
	return (cmd_node);
}

int	parse_heredoc(t_chain **tokens, t_ast *cmd_node)
{
	t_chain	*token;
	t_chain	*next_token;

	if (token->type == TYPE_HEREDOC)
	{
		next_token = token->next;
		if (next_token && (next_token->type == TYPE_WORD
				|| next_token->type == TYPE_QUOTE))
		{
			cmd_node->heredoc = true;
			cmd_node->heredoc_delim = ft_strdup(next_token->value);
		}
		else
		{
			write(2, "bash: syntax error near unexpected token `newline'\n", 52);
			return (2);
		}
		*tokens = token->next->next;
	}
	return (0);
}

int	handle_input_redirection(t_ast *cmd_node, t_chain *token, char *filename)
{
	if (token->type == TYPE_INDIR)
	{
		if (cmd_node->in_file)
			free(cmd_node->in_file);
		cmd_node->in_file = filename;
	}
	else if (token->type == TYPE_HEREDOC)
	{
		if (cmd_node->heredoc_delim)
			free(cmd_node->heredoc_delim);
		cmd_node->heredoc = true;
		cmd_node->heredoc_delim = filename;
	}
	return (0);
}

int	condition_redirection(t_ast *cmd_node, t_chain *token, char *filename)
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
		handle_input_redirection(cmd_node, token, filename);
	return (0);
}
