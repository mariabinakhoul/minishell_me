/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:48:50 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/25 15:18:33 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	parse_input_redirection(t_ast_utils **util, t_token_b **tok)
{
	if ((*tok)->type == TYPE_HEREDOC)
	{
		parse_heredoc(*tok, util);
		if ((*tok)->next && (*tok)->next->type == TOKEN)
		{
			(*util)->in = ft_strdup((*tok)->next->value);
			// if (!(*util)->heredoc)
				// redirect_in(util);
		}
		if ((*tok)->next)
			*tok = (*tok)->next->next;
		return (1);
	}
	return (0);
}

int	parse_output_redirection(t_ast_utils **util, t_token_b **tok)
{
	if ((*tok)->type == TYPE_APPEND)
	{
		if ((*tok)->type == TYPE_APPEND)
			(*util)->append = 1;
		if ((*tok)->next && (*tok)->next->type == TOKEN)
		{
			if ((*util)->out)
				free((*util)->out);
			(*util)->out = ft_strdup((*tok)->next->value);
			//redirect_access_out()
		}
		if ((*tok)->next)
			(*tok) = (*tok)->next->next;
		return (1);
	}
	return (0);
}

int	parse_cmd(t_ast_utils **util, t_token_b **tok)
{
	if ((*tok)->type == TOKEN || (*tok)->type == TYPE_WORD)
	{
		if (!strncmp((*tok)->value, "-n", 2))//might add another condition
		                                                                                                                                                 
	}
	
}