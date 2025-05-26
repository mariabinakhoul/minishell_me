/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:46:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/23 22:17:06 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_ast	*parse_input(t_chain **tokens)
{
	// t_chain	*tokens;

	// tokens = lexer_filler(input);
	if (!tokens)
		return (NULL);
	return (parse_pipeline(tokens));
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
			if (!cmd_node->lexer[*param_count])
				exit(EXIT_FAILURE);
			cmd_node->lexer[*param_count]->t_list = NULL;
			cmd_node->lexer[*param_count]->count = 0;
			if (*tokens)
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

// int	parse_redirection(t_chain **tokens, t_ast *cmd_node)
// {
// 	t_chain	*token;

// 	token = *tokens;

// 	if (!token || !token->next)
// 	{
// 		printf("Error: Missing file name after redirection operator.\n");
// 		if (token)
// 			*tokens = token->next;
// 		return 1;
// 	}
// 	if (token->type == TYPE_OUTDIR)
// 	{
// 		cmd_node->out_file = ft_strdup(token->next->value);
// 		*tokens = token->next->next;
// 	}
// 	else if (token->type == TYPE_APPEND)
// 	{
// 		cmd_node->out_file = ft_strdup(token->next->value);
// 		cmd_node->append = 1;
// 		*tokens = token->next->next;
// 	}
// 	else if (token->type == TYPE_INDIR)
// 	{
// 		cmd_node->in_file = ft_strdup(token->next->value);
// 		*tokens = token->next->next;
// 	}
// 	return 0;
// }

int	parse_redirection(t_chain **tokens, t_ast *cmd_node)
{
	t_chain	*token = *tokens;
	t_chain	*next = token ? token->next : NULL;

	if (!token || !next || (next->type != TYPE_WORD
			&& next->type != TYPE_QUOTE))
	{
		ft_putstr_fd("minishell: syntax error: missing file name after redirection operator.\n", 2);
		*tokens = next ? next->next : NULL;
		return (1);
	}
	char *filename = ft_strdup(next->value);

	if (token->type == TYPE_OUTDIR)
	{
		cmd_node->out_file = filename;
		cmd_node->append = 0;
	}
	else if (token->type == TYPE_APPEND)
	{
		cmd_node->out_file = filename;
		cmd_node->append = 1;
	}
	else if (token->type == TYPE_INDIR)
	{
		cmd_node->in_file = filename;
	}
	else if (token->type == TYPE_HEREDOC)
	{
		cmd_node->heredoc = true;
		cmd_node->heredoc_delim = filename;
	}

	*tokens = next->next;
	return (0);
}
