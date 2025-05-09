/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/09 19:41:26 by nhaber           ###   ########.fr       */
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


void print_ast1(t_ast *node, int depth)
{
    if (!node) {
        printf("(null)\n");
        return;
    }

    for (int i = 0; i < depth; i++)
        printf("  ");
    
    
    if (node->type == CMD) {
        printf("  PARAMS: ");
        if (node->params) {
            for (int i = 0; node->params[i]; i++)
                printf("[%s] ", node->params[i]);
        } else {
            printf("(null)");
        }
        printf("\n");
        
        printf("  REDIRECTIONS: in=%s, out=%s, append=%d\n", 
               node->in_file ? node->in_file : "(null)",
               node->out_file ? node->out_file : "(null)",
               node->append);
    }
    
    printf("  LEFT:\n");
    print_ast1(node->left, depth + 1);
    printf("  RIGHT:\n");
    print_ast1(node->right, depth + 1);
}

// int main(int argc, char **argv, char **envp)
// {
//     set_signals();
//     (void)argc;
//     (void)argv;
//     int exit_code = 0;

//     char *input;
//     while (1)
//     {
//         input = readline("minishell> ");
//         if (!input)
//             break;
//         if (*input)
//             add_history(input);
//         if (strcmp(input, "exit") == 0)
//         {
//             free(input);
//             break;
//         }
//         t_ast *ast = parse_input(input);
//         if (!ast)
//         {
//             free(input);
//             continue;
//         }
//         expand_tree(ast, envp, exit_code);
//         exit_code = execute_command(ast, envp, &exit_code);
//         // print_ast1(ast,100);
//         // free_ast(ast);
// 		free_lexer_nodes(to)
//         free(input);
//     }
//     return 0;
// }
int main(int argc, char **argv, char **envp)
{
    set_signals();
    (void)argc;
    (void)argv;
    int exit_code = 0;

    char *input;
    while (1)
    {
        input = readline("minishell> ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        if (strcmp(input, "exit") == 0)
        {
            printf("exit\n");
            free(input);
            break;
        }

        // Tokenize input into lexer nodes (t_chain)
        t_chain *tokens = lexer_filler(input);  // Lexer node list
        if (!tokens)
        {
            free(input);
            continue;
        }

        // Parse the input into an abstract syntax tree (AST)
        t_ast *ast = parse_input(input);
        if (!ast)
        {
            free(input);
            free_lexer_nodes(tokens);  // Free lexer nodes if parsing fails
            continue;
        }

        // Perform any necessary expansion (environment variable handling, etc.)
        expand_tree(ast, envp, exit_code);

        // Execute the command and update the exit code
        exit_code = execute_command(ast, envp, &exit_code);

        // Optionally print the AST for debugging (this line can be commented out if not needed)
        // print_ast1(ast, 100);

        // Free lexer nodes after processing
        free_lexer_nodes(tokens);  // Free lexer nodes after parsing and execution

        // Free the AST to avoid memory leaks
        free_ast(ast);  // Free AST

        // Free the input after use
        free(input);
    }
    return 0;
}


// int main(int argc, char **argv, char **env)
// {
//     (void) argc;
//     (void) argv;
//     t_env *head = NULL;
//     t_env *envi = NULL;
//     envi = convert_to_list(env);
//     print_env(envi);
//     printf("\n");
//     char **new_env = convert_to_2d(envi);
//     print2d(new_env);
// }