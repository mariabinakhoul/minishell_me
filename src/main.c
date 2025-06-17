/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 17:16:50 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

int	g_exit_code = 0;

t_ast	*validate_tokens_and_parse(t_chain *tokens,
	t_chain *tokens_head, char *input, char **env)
{
	t_ast	*ast;

	if (!tokens)
	{
		free(input);
		return (NULL);
	}
	ast = parse_input(&tokens, env);
	if (!ast)
	{
		free(input);
		free_lexer_nodes(tokens_head);
		return (NULL);
	}
	return (ast);
}

int	process_input_line(char **env, int exit_code)
{
	char	*input;
	t_chain	*tokens;
	t_chain	*tokens_head;
	t_ast	*ast;

	input = readline("minishell> ");
	if (!input)
		return (-1);
	if (*input)
		add_history(input);
	tokens = lexer_filler(input);
	tokens_head = tokens;
	ast = validate_tokens_and_parse(tokens, tokens_head, input, env);
	if (!ast)
		return (exit_code);
	expand_tree(ast, env, exit_code);
	exit_code = execute_command(ast, &env, &exit_code);
	free_lexer_nodes(tokens_head);
	free_ast(ast);
	free(input);
	return (exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_code;
	char	**env;

	set_signals();
	(void)argc;
	(void)argv;
	env = set_env(envp);
	exit_code = 0;
	while (1)
	{
		exit_code = process_input_line(env, exit_code);
		if (exit_code == -1)
			break ;
	}
	if (env)
		free_2d(env);
	return (0);
}
