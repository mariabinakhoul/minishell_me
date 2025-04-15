/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/15 20:17:46 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

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

int main(int argc, char **argv, char **envp)
{
    // set_signals();
    (void)argc;
    (void)argv;
    int last_status = 0;

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
            free(input);
            break;
        }
        t_ast *ast = parse_input(input);
        if (!ast)
        {
            free(input);
            continue;
        }
        expand_tree(ast, envp, last_status);
        last_status = execute_command(ast, envp, &last_status);
        // free_ast(ast);
        free(input);
    }
    return 0;
}
