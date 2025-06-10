/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:13:25 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/09 16:13:52 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_redirection(t_chain **tokens, t_ast *cmd_node)
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
	condition_redirection(cmd_node, token, filename);
	*tokens = next->next;
	return (0);
}
