/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:04:13 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/27 13:26:38 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_tree(t_ast *node, char **env, int exit_code)
{
	if (!node)
		return ;
	if (node->type == CMD)
		expand_command_node(node, env, exit_code);
	expand_tree(node->left, env, exit_code);
	expand_tree(node->right, env, exit_code);
}
