/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:35:09 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/22 08:50:11 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	return_space_type(char c)
{
	if (c == ' ')
		return (TYPE_SPACE);
	if (c == '\t')
		return (TYPE_TAB);
	if (c == '\n')
		return (TYPE_NL);
	if (c == '\0')
		return (TYPE_NL);
	return (0);
}

int	return_operators_type(char c)
{
	if (c == '|')
		return (TYPE_PIPE);
	if (c == '<')
		return (TYPE_INDIR);
	if (c == '>')
		return (TYPE_OUTDIR);
	return (0);
}

int	return_quotes(char c)
{
	if (c == 39)
		return (TYPE_QUOTE);
	if (c == 34)
		return (TYPE_DQUOTE);
	return (0);
}

int	set_lexer_type(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (return_space_type(c));
	if (c == '|' || c == '<' || c == '>')
		return (return_operators_type(c));
	if (c == 39 || c == 34)
		return (return_quotes(c));
	else
		return (TYPE_WORD);
	return (0);
}
