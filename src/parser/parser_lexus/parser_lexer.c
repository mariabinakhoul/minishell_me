/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:48:50 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/01 05:53:35 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


//this function checks if the current token is a heredoc (<<). if 1,
//it assigns the next token's value  as the input file if possible
//then it advances the token pointer
//paramutil: input redirections are available, tok pointer tot he current tok
//return 1 if the heredoc is being proccessed 0 if not 
int	parse_input_redirection(t_ast_utils **util, t_token_b **tok)
{
	if ((*tok)->type == TYPE_HEREDOC)
	{
		parse_heredoc(*tok, util);
		if ((*tok)->next && (*tok)->next->type == TOKEN)
		{
			(*util)->in = ft_strdup((*tok)->next->value);
			if (!(*util)->heredoc)
				redirect_to_in(util);
		}
		if ((*tok)->next)
			*tok = (*tok)->next->next;
		return (1);
	}
	return (0);
}

//same thing but for aappend
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
			redirect_to_out((*util)->out);
		}
		if ((*tok)->next)
			(*tok) = (*tok)->next->next;
		return (1);
	}
	return (0);
}
//this function checks if the current token is a pipe, if 1 it generates 
// a cmd node such as an echo cmd and then it builds the struct ast for 
//the pipe (ig it should be freed need to ask) and we should what's on
// the right to be further built since the let we're done with it ma ela aaze
int		parse_pipeline(t_ast_utils **util, t_token_b **tok)
{
	if ((*tok)->type == TYPE_PIPE)
	{
		(*util)->node = generate_echo_cmd((*util));
		free((*util)->params);
		(*util)->params = NULL;
		(*util)->right = building_pipe(util, tok);
		(*util)->node = make_ast_separator((*util)->node,
				(*util)->right, TYPE_PIPE);
		return (1);
	}
	return (0);
}

//Parses a sequence of tokens to construct for command execution.
//iteration through the token list and processes different type of cmds
//including in and out files redirect. pipelines  and token type,
//it determines if -n flag is present
void	parsing_the_commands(t_ast_utils **util, t_token_b *tok)
{
	while (tok)
	{
		if (parse_input_redirection(util, &tok))
			continue ;
		if (parse_output_redirection(util, &tok))
			continue ;
		if (parse_pipeline(util, &tok))
			break ;
		if (tok->type == TOKEN || (tok->type == TYPE_WORD))
		{
			if (!strncmp(tok->value, "-n", 2))
				(*util)->echo = 1;
			create_cmd_params(tok->value, (*util)->params);
		}
		tok = tok->next;
	}
	(*util)->node = generate_echo_cmd((*util));
}
