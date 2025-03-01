/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:30:30 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/27 17:22:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	parse_heredoc(t_token_b *token, t_ast_utils **util)
{
	if (token->type == TYPE_HEREDOC)
	{
		if (token->extend == -5)
			(*util)->heredoc = 5;
		else
			(*util)->heredoc = 1;
	}
}

//retrieves the current, next and next next from th lexer,
//calls parse heredoc to handle here doc correctly
//it the next token exists it assigns the value to util->in
//in case there's another token, it will update it to two.
//if there's no more tokens, it builds a cmd node using parser_build_cmd
int	parser_in_heroc(t_ast_utils **util, t_lexer **lex, t_token_b **tok)
{
	t_token_b	*current;
	t_token_b	*next;
	t_token_b	*apres;

	current = (*lex)->t_list;
	if (current)
		next = current->next;
	else
		next = current;
	if (next)
		apres = next->next;
	else
		apres = NULL;
	parse_heredoc(current, util);
	if (next && next->type == TOKEN)
	{
		(*util)->in = ft_strdup(next->value);
		if (!(*util)->heredoc)
			redirect_to_in(util);
	}
	if (next && apres)
	{
		*tok = (*tok)->next->next;
		(*lex)->t_list = apres;
	}
	else
	{
		(*util)->node = parser_build_cmd(*util);
		return (1);
	}
	return (0);
}

