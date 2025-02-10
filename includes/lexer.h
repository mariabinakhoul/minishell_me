/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:14:45 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/10 13:04:18 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


typedef enum s_token
{
	TYPE_PIPE = '|',
	TYPE_QUOTE = 39,
	TYPE_DQUOTE = 34,
	TYPE_OUTDIR = '>',
	TYPE_INDIR = '<',
	TYPE_SPACE = ' ',
	TYPE_TAB = '\t',
	TYPE_NP = '\0',
	TYPE_NL = '\n',
	TYPE_WORD,
	APPEND,
}	t_token;

typedef struct s_chain
{
	t_token			type;
	char			*value;
	struct s_chain	*next;
}	t_chain;

int	return_space_type(char c);
int	return_operators_type(char c);
int	return_quotes(char c);


#endif