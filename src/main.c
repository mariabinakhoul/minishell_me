/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/24 22:07:30 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
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
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>  // For chdir()
// #include "minishell.h"  // Include header file for declarations

// void print_ast1(t_ast *node, int depth)
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

//     print_ast1(node->left, depth + 1);
//     print_ast1(node->right, depth + 1);
// }

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     char input[1024];

//     while (1)
//     {
//         printf("minishell> ");
//         if (!fgets(input, sizeof(input), stdin))
//             break;  // Exit on Ctrl+D

//         input[strcspn(input, "\n")] = '\0'; // Remove newline character

//         if (strcmp(input, "exit") == 0)
//             break;

//         // Parse the input and generate the AST (basic handling for just "cd")
//         t_ast *ast = malloc(sizeof(t_ast));  
//         if (!ast)
//         {
//             printf("Memory allocation failed!\n");
//             continue;
//         }
        
//         ast->value = strdup("cd");
//         ast->params = malloc(2 * sizeof(char *));
//         ast->params[0] = strdup("cd");
//         ast->params[1] = strdup("/");  // Change directory to root as a test
//         ast->params[2] = NULL;

//         printf("\n=== AST ===\n");
//         print_ast1(ast, 0);
//         printf("===========\n");

//         // Execute the command based on the AST
//         execute_command(ast, envp);  // This should execute ft_cd()

//         // Free the AST (simplified)
//         free(ast->params[0]);
//         free(ast->params[1]);
//         free(ast->params);
//         free(ast->value);
//         free(ast);
//     }

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv, char **envp)
{
    t_ast cmd;
    char *envp_test[] = {
        "HOME=/home/user",       // Set HOME variable
        "OLDPWD=/home/user/old", // Set OLDPWD variable
        NULL                     // Null-terminate the envp array
    };

    // Initialize cmd structure and set params
    memset(&cmd, 0, sizeof(cmd));

    // Ensure the cmd.params array is properly allocated
    if (argc > 1)  // If an argument is provided, we expect two params (cd and the directory)
    {
        cmd.params = malloc(3 * sizeof(char *));
        if (cmd.params == NULL)
        {
            perror("malloc failed for cmd.params");
            return 1;  // Exit if malloc fails
        }
        cmd.params[0] = strdup("cd");  // Command name
        cmd.params[1] = strdup(argv[1]);  // Directory argument
        cmd.params[2] = NULL;  // Null-terminate
    }
    else  // No arguments provided, so we just want to test cd with no parameters
    {
        cmd.params = malloc(2 * sizeof(char *));
        if (cmd.params == NULL)
        {
            perror("malloc failed for cmd.params");
            return 1;  // Exit if malloc fails
        }
        cmd.params[0] = strdup("cd");  // Command name
        cmd.params[1] = NULL;  // No directory argument, so it should default to HOME or OLDPWD
    }

    // Ensure strdup did not fail
    if (!cmd.params[0] || (argc > 1 && !cmd.params[1]))
    {
        perror("strdup failed");
        return 1;  // Exit if strdup fails
    }

    // Set up environment for testing
    if (envp_test[0] != NULL)
        envp = envp_test;

    // Test the ft_cd function with different cases
    printf("Test 1: No arguments (cd)\n");
    ft_cd(&cmd, envp);

    printf("\nTest 2: cd with - argument (cd -)\n");
    cmd.params[1] = strdup("-");  // Simulate "cd -"
    ft_cd(&cmd, envp);

    printf("\nTest 3: cd with an invalid directory (cd /nonexistent)\n");
    cmd.params[1] = strdup("/nonexistent");  // Simulate "cd /nonexistent"
    ft_cd(&cmd, envp);

    printf("\nTest 4: cd with a valid directory (cd /tmp)\n");
    cmd.params[1] = strdup("/tmp");  // Simulate "cd /tmp"
    ft_cd(&cmd, envp);

    // Clean up memory
    if (cmd.params)
    {
        for (int i = 0; cmd.params[i]; i++)
            free(cmd.params[i]);
        free(cmd.params);
    }

    return 0;
}