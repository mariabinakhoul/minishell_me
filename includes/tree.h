/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:45:16 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/22 20:50:56 by mabi-nak         ###   ########.fr       */
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
	char					*heredoc_content;
	char					*heredoc_delim;
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

t_ast	*parse_input(t_chain **tokens);
t_ast		*parse_pipeline(t_chain **tokens);
t_ast		*parse_command(t_chain **tokens);
int			parse_redirection(t_chain **tokens, t_ast *cmd_node);
char		*join_and_free(char *s1, const char *s2);
char		*join_and_free_char(char *s, char c);
char		*get_env_value(char *var, char **env);
char		*expand_argument(char *arg, int quoted, char **env,
				int exit_code);
void		expand_command_node(t_ast *cmd, char **env, int exit_code);
void		expand_tree(t_ast *node, char **env, int exit_code);

#endif