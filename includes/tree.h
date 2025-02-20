/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:45:16 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/18 13:09:18 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H
# include "minishell.h"

// typedef enum e_ast_type
// {
// 	CMD,
// 	PIPE,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	HEREDOC,
// 	APPEND,
// }	t_ast_type;

typedef struct s_ast
{
	t_token		type;
	char		value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

#endif