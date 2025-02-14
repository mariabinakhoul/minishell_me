/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:14:45 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/14 12:59:39 by mabi-nak         ###   ########.fr       */
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
	TYPE_APPEND,
	TYPE_HEREDOC,
	STATE_ANY,
}	t_token;

typedef struct s_chain
{
	t_token			type;
	char			*value;
	struct s_chain	*next;
}	t_chain;

int		return_space_type(char c);
int		return_operators_type(char c);
int		return_quotes(char c);
int		set_lexer_type(char c);
t_chain	*create_new_node(t_token type, char *value);
t_chain	*lexer_filler(char *str);
char	*ft_strndup(const char *src, int n);
t_chain	*current_node_helper(char *str, int *i,
			t_chain **head, t_chain **current);
t_chain	*handle_single_quotes(char *str, int *i,
			t_chain **head, t_chain **current);
t_chain	*handle_double_quotes(char *str, int *i,
			t_chain **head, t_chain **current);

#endif