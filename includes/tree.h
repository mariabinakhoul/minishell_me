/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:45:16 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/11 18:49:57 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include "minishell.h"

typedef enum e_ast_type
{
	CMD,
	PIPE,
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type				type;
	char					*value;
	struct s_ast			*left;
	struct s_ast			*right;
	char					*in_file;
	char					*out_file;
	char					**params;
	int						append;
	int						heredoc;
	int						exit;
	struct s_syntax_tree	*tree_link;
	struct s_lexer			**lexer;
}	t_ast;

typedef struct s_ast_utils
{
	char	*params;
	char	*out;
	char	*in;
	t_ast	*right;
	int		append;
	int		heredoc;
	t_ast	*node;
	int		echo;
	int		exit;
	bool	has_pipeline;
	bool	has_redirection;
}	t_ast_utils;

typedef struct s_l_engine
{
	t_token	*tok_chain;
	t_token	*current_tok;
	int		count;
}	t_l_engine;

typedef struct s_syntax_tree
{
	struct s_ast	*branch;
}	t_syntax_tree;

typedef struct s_lexer
{
	t_token_b	*t_list;
	int			count;
}	t_lexer;

void		parse_heredoc(t_token_b *token, t_ast_utils **util);
int			parse_input_redirection(t_ast_utils **util, t_token_b **tok);
int			parse_output_redirection(t_ast_utils **util, t_token_b **tok);
t_ast		*generate_echo_cmd(t_ast_utils *util);
t_ast		*make_ast_separator(t_ast *left, t_ast *right, int type);
int			parse_pipeline1(t_ast_utils **util, t_lexer **lex, t_token_b **tok);
int			parser_in_heroc(t_ast_utils **util, t_lexer **lex, t_token_b **tok);
void		parsing_the_commands(t_ast_utils **util, t_lexer **lex,
				t_token_b *tok);
void		make_cmd_ast(t_ast *node, t_ast *util);
void		redirect_to_in(t_ast_utils **util);
void		redirect_to_out(char *filename);
t_ast_utils	*make_util_ast(t_ast_utils **util);
t_ast		*building_pipe(t_lexer **lex, t_token_b *tok);
char		*create_cmd_params(char *value, char *params);
t_ast		*parser_build_tree(t_lexer **lex, t_token_b *tok);
void		expand_tree(t_ast *node);

#endif