/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/22 08:48:27 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes

// void print_list(t_chain *list) {
//     while (list) {
//         printf("Type: %d, Value: %s\n", list->type, list->value);
//         list = list->next;
//     }
// }



// int main(int argc, char *argv[]) {
//     if (argc < 2) {
//         printf("Usage: %s <input_string>\n", argv[0]);
//         return 1;
//     }

//     // Calculate total length for concatenation
//     int total_length = 0;
//     for (int i = 1; i < argc; i++) {
//         total_length += strlen(argv[i]) + 1; // +1 for space or null terminator
//     }

//     // Allocate and concatenate arguments
//     char *input = malloc(total_length);
//     if (!input) return 1;
//     input[0] = '\0';

//     for (int i = 1; i < argc; i++) {
//         strcat(input, argv[i]);
//         if (i < argc - 1) strcat(input, " ");
//     }

//     t_chain *list = lexer_filler(input);

//     print_list(list);

//     // Free memory
//     t_chain *temp;
//     while (list) {
//         temp = list;
//         list = list->next;
//         free(temp->value);
//         free(temp);
//     }
//     free(input);

//     return 0;
// }

void print_list(t_chain *list) {
    while (list) {
        printf("Type: %d, Value: %s\n", list->type, list->value);
        list = list->next;
    }
}

t_ast *build_ast(t_chain *tokens)
{
    if (!tokens)
        return NULL;
    return split_at_last_pipe(tokens);
}

// Helper function to print the AST
void print_ast(t_ast *ast, int depth)
{
    if (!ast)
        return;

    // Print indentation based on depth
    for (int i = 0; i < depth; i++)
        printf("  ");

    // Print the current node
    printf("Type: %d, Value: %s\n", ast->type, ast->value);

    // Recursively print left and right subtrees
    print_ast(ast->left, depth + 1);
    print_ast(ast->right, depth + 1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    // Calculate total length for concatenation
    int total_length = 0;
    for (int i = 1; i < argc; i++)
    {
        total_length += strlen(argv[i]) + 1; // +1 for space or null terminator
    }

    // Allocate and concatenate arguments
    char *input = malloc(total_length);
    if (!input) return 1;
    input[0] = '\0';

    for (int i = 1; i < argc; i++)
    {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " ");
    }

    // Tokenize the input string
    t_chain *tokens = lexer_filler(input);

    // Print the token list (for debugging)
    printf("Tokens:\n");
    print_list(tokens);

    // Build the AST from the tokens
    t_ast *ast = build_ast(tokens);

    // Print the AST structure
    printf("\nAST:\n");
    print_ast(ast, 0);

    // Free memory
    t_chain *temp;
    while (tokens)
    {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
    free(input);

    // Free the AST (you need to implement this function)
    return 0;
}
// void free_ast(t_ast *ast)
// {
//     if (ast)
//     {
//         if (ast->params)
//         {
//             for (int i = 0; ast->params[i]; i++)
//                 free(ast->params[i]);
//             free(ast->params);
//         }
//         free(ast);
//     }
// }

// // Helper function to create a chain from a string
// t_chain *create_chain(char *value, int type)
// {
//     t_chain *chain = malloc(sizeof(t_chain));
//     if (!chain)
//         return (NULL);
//     chain->value = ft_strdup(value); // Assuming ft_strdup is available
//     chain->type = type;
//     chain->next = NULL;
//     return (chain);
// }

// int main(int argc, char **argv)
// {
//     if (argc < 2)
//     {
//         printf("Usage: %s <command> [args...]\n", argv[0]);
//         return (1);
//     }

//     // Create chains from argv
//     t_chain *head = NULL;
//     t_chain *prev = NULL;

//     for (int i = 1; i < argc; i++)
//     {
//         // Assume type 0 for regular chains (replace with actual chain type if needed)
//         t_chain *chain = create_chain(argv[i], 0);
//         if (!chain)
//         {
//             printf("Error: Failed to create chain.\n");
//             return (1);
//         }

//         if (!head)
//             head = chain; // First chain
//         else
//             prev->next = chain; // Link to previous chain

//         prev = chain; // Update previous chain
//     }

//     // Pointer to the first chain
//     t_chain *chain = head;

//     // Build the simple command
//     t_ast *ast = parser_build_cmd(&chain);

//     // Check if the AST was created successfully
//     if (!ast)
//     {
//         printf("Error: Failed to create AST.\n");
//         return (1);
//     }

//     // Print the result
//     printf("Command: %s\n", ast->params[0]);
//     for (int i = 1; ast->params[i]; i++)
//         printf("Argument %d: %s\n", i, ast->params[i]);

//     // Free the AST
//     free_ast(ast);

//     // Free the chains
//     while (head)
//     {
//         t_chain *temp = head;
//         head = head->next;
//         free(temp->value);
//         free(temp);
//     }

//     return (0);
// }
