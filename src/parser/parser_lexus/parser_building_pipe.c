/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_building_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 20:10:10 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/11 18:50:05 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	process_token(t_lexer **lex, t_ast_utils **util, t_token_b **tok)
{
	t_token_b	*token;

	token = (*lex)->t_list;
	if (token->type == TOKEN)
		parsing_the_commands(util, lex, (*tok));
	else if (parse_input_redirection(util, (t_token_b **)tok)
		|| parse_output_redirection(util, (t_token_b **)tok))
		(*util)->has_redirection = true;
	else if (parse_pipeline1(util, lex, (t_token_b **)tok))
		(*util)->has_pipeline = true;
}

static int	handle_token_advancement(t_lexer **lex, t_ast_utils **util,
	t_token_b **tok)
{
	t_token_b	*token;

	token = (*lex)->t_list;
	if (!token)
		return (0);
	if (!(*util)->has_redirection)
	{
		(*tok) = (*tok)->next;
		(*lex)->t_list = (*lex)->t_list->next;
	}
	if ((*util)->has_redirection)
	{
		(*tok) = NULL;
		(*lex)->t_list = NULL;
	}
	return (1);
}

t_ast	*building_pipe(t_lexer **lex, t_token_b *tok)
{
	t_ast_utils	*util;
	t_ast		*node;

	make_util_ast(&util);
	util->has_pipeline = false;
	util->has_redirection = false;
	(*lex)->t_list = (*lex)->t_list->next;
	tok = tok->next;
	while (((*lex)->t_list))
	{
		util->has_redirection = false;
		process_token(lex, &util, &tok);
		if (!handle_token_advancement(lex, &util, &tok))
			break ;
	}
	if (!util->node)
		util->node = generate_echo_cmd(util);
	node = util->node;
	free(util->params);
	free(util);
	return (node);
}
