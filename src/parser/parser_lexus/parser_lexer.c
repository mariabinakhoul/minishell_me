/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:48:50 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/24 18:36:02 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parser_build_cmd(t_ast_utils *lexer)
{
	t_ast	*node;
	char	*param;

	if (!lexer || !(param = lexer_filler(lexer)))
		return (NULL);
	node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!node)
		returrn (NULL);
	node->type = CMD;
	node->params = NULL;
	node->out_file = NULL;
	node->append = 0;

}
