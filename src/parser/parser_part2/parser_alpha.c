/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:46:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/03 16:05:12 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast	*parse_input(char *input)
{
	t_chain	*tokens;

	tokens = lexer_filler(input);
	if (!tokens)
		return (NULL);
	return (parse_pipeline(&tokens));
}

t_ast	*parse_pipeline(t_chain **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipe_node;

	left = parse_command(tokens);
	while (*tokens && (*tokens)->type == TYPE_PIPE)
	{
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
			cmd_node->params = (char **)safe_expand_array(
					(void **)cmd_node->params, *param_count, *param_count + 2);
			cmd_node->params[*param_count] = ft_strdup((*tokens)->value);
			cmd_node->lexer = (struct s_lexer **)safe_expand_array(
					(void **)cmd_node->lexer, *param_count, *param_count + 2);
			cmd_node->lexer[*param_count] = malloc(sizeof(struct s_lexer));
			cmd_node->lexer[*param_count]->t_list = NULL;
			cmd_node->lexer[*param_count]->count = (*tokens)->quote;
			cmd_node->lexer[*param_count + 1] = NULL;
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


int parse_heredoc(t_chain **tokens, t_ast *cmd_node)
{
	t_chain	*token;
	if (token->type == TYPE_HEREDOC)
	{
		t_chain *next_token = token->next;
		if (next_token && (next_token->type == TYPE_WORD || next_token->type == TYPE_QUOTE))
		{
			cmd_node->heredoc = true;
			cmd_node->heredoc_delim = ft_strdup(next_token->value);
		}
		else
		{
			write(2, "bash: syntax error near unexpected token `newline'\n", 52);
			// exit_code = 2;
			return 2;
			// *tokens= token->next;
		}
		*tokens = token->next->next;
	}
	return 0;
}

void	parse_redirection(t_chain **tokens, t_ast *cmd_node)
{
	t_chain	*token;

	token = *tokens;
	if (token->type == TYPE_OUTDIR)
	{
		cmd_node->out_file = ft_strdup(token->next->value);
		if (cmd_node->out_file == NULL)
			*tokens = token->next;
		*tokens = token->next->next;
	}
	else if (token->type == TYPE_APPEND)
	{
		cmd_node->out_file = ft_strdup(token->next->value);
		cmd_node->append = 1;
		*tokens = token->next->next;
	}
	else if (token->type == TYPE_INDIR)
	{
		cmd_node->in_file = ft_strdup(token->next->value);
		*tokens = token->next->next;
	}
}
