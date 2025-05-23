/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/23 18:57:07 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

int exit_code = 0;


// int	main(int argc, char **argv, char **envp)
// {
// 	int		exit_code;
// 	char	*input;
// 	char	**env;
// 	t_chain	*tokens;
// 	t_ast	*ast;

// 	set_signals();
// 	(void)argc;
// 	(void)argv;
// 	env = set_env(envp);
// 	exit_code = 0;
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 			break ;
// 		if (*input)
// 			add_history(input);
// 		tokens = lexer_filler(input);
// 		if (!tokens)
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		ast = parse_input(input);
// 		if (!ast)
// 		{
// 			free(input);
// 			free_lexer_nodes(tokens);
// 			continue ;
// 		}
// 		expand_tree(ast, env, exit_code);
// 		exit_code = execute_command(ast, &env, &exit_code);
// 		free_lexer_nodes(tokens);
// 		free_ast(ast);
// 		free(input);
// 	}
// 	return (0);
// }

void print_lexer_list(t_chain *head)
{
    int count = 0;
    while (head)
    {
        printf("Token %d: type=%d, value='%s'\n", count, head->type, head->value);
        head = head->next;
        count++;
    }
}

int main(int argc, char **argv, char **envp)
{
    int     exit_code;
    char    *input;
    char    **env;
    t_chain *tokens;
    t_chain *tokens_head;
    t_ast   *ast;

    set_signals();
    (void)argc;
    (void)argv;

    env = set_env(envp);
    exit_code = 0;
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break ;
        if (*input)
            add_history(input);

        tokens = lexer_filler(input);
        tokens_head = tokens;

        if (!tokens)
        {
            free(input);
            continue;
        }
        ast = parse_input(&tokens);
        if (!ast)
        {
            free(input);
            free_lexer_nodes(tokens_head);
            continue;
        }

        expand_tree(ast, env, exit_code);
        exit_code = execute_command(ast, &env, &exit_code);
		// printf("HERE!\n");
        free_lexer_nodes(tokens_head);
        free_ast(ast);
        free(input);

        // Free old environment before reassigning new one
        free_2d(env);  
        // env = set_env(envp);  // Reassign environment
    }
    free_2d(env);  // Free at the end of the program

    return (0);
}
