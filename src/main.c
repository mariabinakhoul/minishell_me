/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/18 17:07:59 by mabi-nak         ###   ########.fr       */
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

t_chain	*read_and_tokenize(char **input)
{
	t_chain	*tokens;

	*input = readline("minishell> ");
	if (!*input)
		return (NULL);
	if (**input)
		add_history(*input);
	tokens = lexer_filler(*input);
	if (!tokens)
	{
		free(*input);
		return (NULL);
	}
	return (tokens);
}

int	process_input_loop(char ***env, int exit_code)
{
	char	*input;
	t_chain	*tokens;
	t_chain	*tokens_head;
	t_ast	*ast;

	tokens = read_and_tokenize(&input);
	tokens_head = tokens;
	if (!tokens)
		return (exit_code);
	ast = parse_input(&tokens, *env);
	if (!ast)
	{
		free(input);
		free_lexer_nodes(tokens_head);
		return (exit_code);
	}
	expand_tree(ast, *env, exit_code);
	exit_code = execute_command(ast, env, &exit_code);
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
		exit_code = process_input_loop(&env, exit_code);
	if (env)
		free_2d(env);
	return (0);
}
