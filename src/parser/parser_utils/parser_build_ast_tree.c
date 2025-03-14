/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_ast_tree.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:14:37 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/11 18:50:28 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	process_token(t_lexer **lex, t_ast_utils **util,
	int *flag, t_token_b *tok)
{
	t_token_b	*token;

	token = (*lex)->t_list;
	if (token->type == TOKEN)
	{
		printf("TEST2\n");
		generate_echo_cmd(*util);
	}
	else if (parse_input_redirection(util, &tok)
		|| parse_output_redirection(util, &tok))
	{
		if (*flag == 0)
			(*flag)++;
		else
			(*flag) += 2;
	}
	else if (token->type == TYPE_PIPE
		&& parse_pipeline1(util, lex, (t_token_b **)tok))
	{
		printf("TEST3\n");
		(*util)->has_pipeline = true;
	}
	printf(":BUXINO\n");
}

void	update_tokens(t_lexer **lex, t_token_b **tok, int flag)
{
	if (flag == 0 || flag == 2)
	{
		(*tok) = (*tok)->next;
		(*lex)->t_list = (*lex)->t_list->next;
		// printf ("PART @@@@\n");
	}
	// printf("IM HERRRRE\n");
}

t_ast	*parser_build_tree(t_lexer **lex, t_token_b *tok)
{
	t_ast_utils	*util;
	t_ast		*node;
	int			flag;


	make_util_ast(&util);

	while ((*lex)->t_list && tok)
	{
		flag = 0;
		printf("Debug processing token type = %d, value = %s\n", tok->type, tok->value);
		process_token(lex, &util, &flag, tok);
		update_tokens(lex, &tok, flag);
	}
	if (!util->node)
	{
		printf("Debug: Generating echo cmd as fallback\n");
		util->node = generate_echo_cmd(util);
	}	
	node = util->node;
	if (node)
	{
		printf("AST Node: Type = %d, Params = ", node->type);
		for (int i = 0; node->params && node->params[i]; i++)
			printf("%s", node->params[i]);
		printf("\n");
	}
	free(util->params);
	free(util);
	return (node);
}
