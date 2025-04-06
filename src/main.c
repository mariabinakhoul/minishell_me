/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/06 22:18:30 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>

// #include "minishell.h"
// void print_ast(t_ast *node, int depth)
// {
//     if (!node)
//         return;

//     for (int i = 0; i < depth; i++)
//         printf("  ");  // Indentation for tree structure

//     if (node->type == CMD)
//     {
//         printf("CMD: ");
//         for (int i = 0; node->params && node->params[i]; i++)
//             printf("[%s] ", node->params[i]);
//         if (node->in_file)
//             printf("(IN: %s) ", node->in_file);
//         if (node->out_file)
//             printf("(OUT: %s, APPEND: %d) ", node->out_file, node->append);
//         printf("\n");
//     }
//     else if (node->type == PIPE)
//     {
//         printf("PIPE\n");
//     }

//     print_ast(node->left, depth + 1);
//     print_ast(node->right, depth + 1);
// }

// int main(void)
// {
//     char input[1024];

//     while (1)
//     {
//         printf("minishell> ");
//         if (!fgets(input, sizeof(input), stdin))
//             break;  // Exit on Ctrl+D

//         input[strcspn(input, "\n")] = '\0'; // Remove newline character

//         if (strcmp(input, "exit") == 0)
//             break;

//         t_ast *ast = parse_input(input);
//         if (!ast)
//         {
//             printf("Parsing error!\n");
//             continue;
//         }

//         printf("\n=== AST ===\n");
//         print_ast(ast, 0);
//         printf("===========\n");

//         // Free AST (implement a function for cleanup)
//     }

//     return 0;
// }
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For chdir()
#include "minishell.h"  // Include header file for declarations
void print_ast1(t_ast *node, int depth)
{
    if (!node) {
        printf("(null)\n");
        return;
    }

    for (int i = 0; i < depth; i++)
        printf("  ");
    
    // printf("AST NODE: type=%d, value=%s\n", node->type, node->value ? node->value : "(null)");
    
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
    (void)argc;
    (void)argv;
    int last_status = 0;  // Local variable for tracking last status
    // int i = 0;

    // Print out the environment variables for debugging.
    // printf("Environment variables:\n");
    // while (envp[i])
    // {
    //     printf("env[%d]: %s\n", i, envp[i]);
    //     i++;
    // }
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
            printf("Failed to parse input\n");
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

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;

//     ft_export(envp);

//     return 0;
// }



// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     ft_setenv(envp,"Libft");
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// int main(int argc, char **argv, char **envp)
// {
//     t_ast cmd;
//     char **envp_copy = NULL;
//     int env_size = 0;

//     // Create a modifiable copy of the environment
//     while (envp[env_size]) env_size++;
//     envp_copy = malloc((env_size + 1) * sizeof(char *));
//     for (int i = 0; i < env_size; i++) {
//         envp_copy[i] = strdup(envp[i]);
//     }
//     envp_copy[env_size] = NULL;

//     // Initialize cmd structure
//     memset(&cmd, 0, sizeof(cmd));
//     cmd.params = malloc(3 * sizeof(char *));
//     cmd.params[0] = strdup("cd");
    
//     if (argc > 1) {
//         cmd.params[1] = strdup(argv[1]);
//         cmd.params[2] = NULL;
//     } else {
//         cmd.params[1] = NULL;
//     }

//     printf("Current directory before: %s\n", getcwd(NULL, 0));

//     // Test cases
//     printf("\nTest 1: No arguments (cd)\n");
//     ft_cd(&cmd, &envp_copy);

//     if (cmd.params[1]) free(cmd.params[1]);
//     printf("\nTest 2: cd with - argument (cd -)\n");
//     cmd.params[1] = strdup("-");
//     ft_cd(&cmd, &envp_copy);

//     if (cmd.params[1]) free(cmd.params[1]);
//     printf("\nTest 3: cd with an invalid directory (cd /nonexistent)\n");
//     cmd.params[1] = strdup("/nonexistent");
//     ft_cd(&cmd, &envp_copy);

//     if (cmd.params[1]) free(cmd.params[1]);
//     printf("\nTest 4: cd with a valid directory (cd /tmp)\n");
//     cmd.params[1] = strdup("/tmp");
//     ft_cd(&cmd, &envp_copy);

//     printf("Current directory after: %s\n", getcwd(NULL, 0));

//     // Clean up
//     free(cmd.params[0]);
//     if (cmd.params[1]) free(cmd.params[1]);
//     free(cmd.params);

//     for (int i = 0; envp_copy[i]; i++) {
//         free(envp_copy[i]);
//     }
//     free(envp_copy);

//     return 0;
// }