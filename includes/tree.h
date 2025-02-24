/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:45:16 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/24 18:29:45 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include "minishell.h"

typedef enum e_ast_type
{
	CMD,
	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	HEREDOC,

}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*in_file;
	char			*out_file;
	char			**params;
	int				append;
	int				heredoc;
	int				exit;
}	t_ast;

typedef struct s_ast_utils
{
	char	*params;
	char	*out;
	char	*in;
	int		append;
	int		heredoc;
	t_ast	*node;
	int		echo;
}	t_ast_utils;

typedef struct s_l_engine
{
	t_token	*tok_chain;
	t_token	*current_tok;
	int		count;
}	t_l_engine;

int		count_args(t_chain *tokens);
int		find_last_pipe(t_chain	*tokens);
char	**get_args_from_the_tokens(t_chain *tokens);
t_ast	*split_at_last_pipe(t_chain *tokens);
t_ast	*parser_build_cmd(t_ast_utils *util);
char	**realloc_params(char **params, int p_count, char *value);


#endif