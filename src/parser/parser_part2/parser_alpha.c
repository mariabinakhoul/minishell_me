/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:46:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/11 21:27:16 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast	*pars_input(char *input)
{
	t_chain	*tokens;

	tokens = lexer_filler(input);
	if (!tokens)
		return (NULL);
	return (parse_pipeline(&tokens));
}

t_ast	*pars_pipeline(t_chain **tokens)
{
	t_ast	*left;
	t_chain	*pipe_token;
	t_ast	*right;
	t_ast	*right;
	t_ast	*pipe_node;

	left = parse_command(tokens);
	while (*tokens && (*tokens)->type == TYPE_PIPE)
	{
		pipe_token = *tokens;
		*tokens = (*tokens)->next;
		right = parse_command(tokens);
		if (!right)
			return (NULL);
		pipe_node = malloc(sizeof(t_ast));
		pipe_node->type = PIPE;
		pipe_node->left = left;
		pipe_node->right = right;
		pipe_node->value = strdup("|");
		left = pipe_node;
	}
	return (left);
}

t_ast	*parse_command(t_chain **tokens)
{
	t_ast	*cmd_node;
	int		param_count;

	cmd_node = malloc(sizeof(t_ast));
	cmd_node->type = CMD;
	cmd_node->params = NULL;
	param_count = 0;
	if ((!(*tokens)) || (*tokens)->type == TYPE_PIPE)
		return (NULL);
	while (*tokens && (*tokens)->type != TYPE_PIPE)
	{
		if (*tokens && (*tokens)->type != TYPE_INDIR
			|| (*tokens)->type == TYPE_OUTDIR)
			parse_redirection(tokens, cmd_node);
		else
		{
			cmd_node->params = ft_realloc(cmd_node->params,
					sizeof(char *) * (param_count + 2));
			cmd_node->params[param_count++] = ft_strdup((*tokens)->value);
			cmd_node->params[param_count] = NULL;
			*tokens = (*tokens)->next;
		}
	}
	return (cmd_node);
}

void	parse_redirection(t_chain **tokens, t_ast *cmd)
{
	t_token	type;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (!*tokens)
		return ;
	if (type == TYPE_INDIR)
		cmd->in_file = ft_strdup((*tokens)->value);
	else if (type == TYPE_OUTDIR)
	{
		cmd->out_file = ft_strdup ((*tokens)->value);
		cmd->append = 0;
	}
	else if (type == TYPE_APPEND)
	{
		cmd->out_file = ft_strdup((*tokens)->value);
		cmd->append = 1;
	}
	else if (type == TYPE_HEREDOC)
	{
		cmd->in_file = ft_strdup((*tokens)->value);
		cmd->heredoc = 1;
	}
	*tokens = (*tokens)->next;
}