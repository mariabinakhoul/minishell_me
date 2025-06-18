/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:46:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/16 16:36:50 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_pipe_syntax(t_chain *curr)
{
	if (curr->type == TYPE_PIPE)
	{
		if (!curr->next)
		{
			ft_putstr_fd("minishell: syntax error near "
				"unexpected token `|'\n", 2);
			return (1);
		}
		if (curr->next->type == TYPE_PIPE)
		{
			ft_putstr_fd("minishell: syntax error near "
				"unexpected token `|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	validate_pipeline_syntax(t_chain *tokens)
{
	t_chain	*curr;
	int		result;

	curr = tokens;
	if (!curr)
		return (0);
	if (curr->type == TYPE_PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (curr)
	{
		result = check_pipe_syntax(curr);
		if (result == 1)
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_ast	*parse_input(t_chain **tokens, char **env)
{
	if (!tokens || !*tokens)
		return (NULL);
	if (validate_pipeline_syntax(*tokens))
		return (NULL);
	return (parse_pipeline(tokens, env));
}

t_ast	*parse_pipeline(t_chain **tokens, char **env)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipe_node;

	left = parse_command(tokens, env);
	while (*tokens && (*tokens)->type == TYPE_PIPE)
	{
		*tokens = (*tokens)->next;
		right = parse_command(tokens, env);
		if (!right)
			return (NULL);
		pipe_node = ft_calloc(1, sizeof(t_ast));
		if (!pipe_node)
			return (NULL);
		pipe_node->type = PIPE;
		pipe_node->left = left;
		pipe_node->right = right;
		pipe_node->value = strdup("|");
		left = pipe_node;
	}
	return (left);
}

void	expand_params_and_lexer(t_ast *cmd_node, t_chain *token,
	int *param_count)
{
	cmd_node->params = (char **)safe_expand_array(
			(void **)cmd_node->params, *param_count, *param_count + 2);
	cmd_node->params[*param_count] = ft_strdup(token->value);
	cmd_node->lexer = (struct s_lexer **)safe_expand_array(
			(void **)cmd_node->lexer, *param_count, *param_count + 2);
	cmd_node->lexer[*param_count] = malloc(sizeof(struct s_lexer));
	if (!cmd_node->lexer[*param_count])
		exit(EXIT_FAILURE);
	cmd_node->lexer[*param_count]->t_list = NULL;
	cmd_node->lexer[*param_count]->count = 0;
	if (token)
		cmd_node->lexer[*param_count]->count = token->quote;
	cmd_node->lexer[*param_count + 1] = NULL;
}
