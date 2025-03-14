/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/10 22:00:45 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "minishell.h"

void free_tokens(t_chain *tokens) {
    t_chain *temp;
    while (tokens) {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}

void free_token_b(t_token_b *tokens) {
    t_token_b *temp;
    while (tokens) {
        temp = tokens;
        tokens = tokens->next;
        free(temp->value);
        free(temp);
    }
}

void free_ast(t_ast *node) {
    if (node) {
        if (node->params) {
            for (int i = 0; node->params[i]; i++) {
                free(node->params[i]);
            }
            free(node->params);
        }
        free_ast(node->left);
        free_ast(node->right);
        free(node);
    }
}

t_token_b *convert_chain_to_token_b(t_chain *tokens)
{
    t_token_b *head = NULL;
    t_token_b *current = NULL;

    while (tokens)
    {
        t_token_b *new_token = malloc(sizeof(t_token_b));
        if (!new_token)
            return NULL;
        new_token->value = ft_strdup(tokens->value);
        new_token->type = tokens->type;
        new_token->next = NULL;
        if (!head)
            head = new_token;
        else
            current->next = new_token;
        current = new_token;
        tokens = tokens->next;
    }

    return head;
}

void print_ast(t_ast *node)
{
    if (!node)
        return;

    printf("Node Type: %d\n", node->type);
    if (node->params)
    {
        printf("Params: ");
        for (int i = 0; node->params[i]; i++)
            printf("%s ", node->params[i]);
        printf("\n");
    }

    if (node->in_file)
        printf("Input File: %s\n", node->in_file);
    if (node->out_file)
        printf("Output File: %s\n", node->out_file);

    print_ast(node->left);
    print_ast(node->right);
}

t_ast *new_ast_node(int type, char *value)
{
    t_ast *node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

t_ast *parse_tokens(t_token_b **tokens)
{
    if (!tokens || !*tokens)
        return NULL;

    t_ast *left = new_ast_node((*tokens)->type, (*tokens)->value);
    *tokens = (*tokens)->next; // Move to the next token

    while (*tokens)
    {
        if ((*tokens)->type == PIPE) // If it's a pipe, create a new AST node
        {
            t_ast *pipe_node = new_ast_node(PIPE, (*tokens)->value);
            *tokens = (*tokens)->next; // Move past "|"
            pipe_node->left = left;    // Left subtree is the previous command
            pipe_node->right = parse_tokens(tokens); // Right subtree is next command
            return pipe_node;
        }
        *tokens = (*tokens)->next; // Move to next token
    }
    return left; // Return the final tree
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    // Step 1: Lexer - Tokenize the input string
    t_chain *tokens = lexer_filler(argv[1]);
    if (!tokens)
    {
        printf("Lexer failed to tokenize the input.\n");
        return 1;
    }

    // Step 2: Convert t_chain to t_token_b
    t_token_b *token_list = convert_chain_to_token_b(tokens);
    if (!token_list)
    {
        printf("Failed to convert tokens.\n");
        return 1;
    }

    // Step 3: Parser - Build the AST
    t_lexer *lexer = malloc(sizeof(t_lexer));  // Dynamically allocate lexer
    if (!lexer)
    {
        printf("Failed to allocate memory for lexer.\n");
        return 1;
    }
    lexer->t_list = token_list;  // Assign the token list to lexer

    t_ast *ast = parser_build_tree(&lexer, token_list);  // Pass the address of lexer
    // if (!ast)
    // {
    //     printf("Parser failed to build the AST.\n");
    //     return 1;
    // }

    // Step 4: Print or Execute the AST
    print_ast(ast);  // Assuming you have a function to print the AST
    // execute_ast(ast);  // Assuming you have a function to execute the AST

    // Step 5: Cleanup
    free_tokens(tokens);  // Implement this function to free t_chain
    free_token_b(token_list);  // Implement this function to free t_token_b
    free_ast(ast);  // Implement this function to free the AST
    free(lexer);  // Free the dynamically allocated lexer

    return 0;
}

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

// void print_list(t_chain *list) {
//     while (list) {
//         printf("Type: %d, Value: %s\n", list->type, list->value);
//         list = list->next;
//     }
// }



// // Helper function to print the AST
// void print_ast(t_ast *ast, int depth)
// {
//     if (!ast)
//         return;

//     // Print indentation based on depth
//     for (int i = 0; i < depth; i++)
//         printf("  ");

//     // Print the current node
//     printf("Type: %d, Value: %s\n", ast->type, ast->value);

//     // Recursively print left and right subtrees
//     print_ast(ast->left, depth + 1);
//     print_ast(ast->right, depth + 1);
// }

// int main(int argc, char *argv[])
// {
//     if (argc < 2)
//     {
//         printf("Usage: %s <input_string>\n", argv[0]);
//         return 1;
//     }

//     // Calculate total length for concatenation
//     int total_length = 0;
//     for (int i = 1; i < argc; i++)
//     {
//         total_length += strlen(argv[i]) + 1; // +1 for space or null terminator
//     }

//     // Allocate and concatenate arguments
//     char *input = malloc(total_length);
//     if (!input) return 1;
//     input[0] = '\0';

//     for (int i = 1; i < argc; i++)
//     {
//         strcat(input, argv[i]);
//         if (i < argc - 1) strcat(input, " ");
//     }

//     // Tokenize the input string
//     t_chain *tokens = lexer_filler(input);

//     // Print the token list (for debugging)
//     printf("Tokens:\n");
//     print_list(tokens);

//     // Build the AST from the tokens
//     t_ast *ast = build_ast(tokens);

//     // Print the AST structure
//     printf("\nAST:\n");
//     print_ast(ast, 0);

//     // Free memory
//     t_chain *temp;
//     while (tokens)
//     {
//         temp = tokens;
//         tokens = tokens->next;
//         free(temp->value);
//         free(temp);
//     }
//     free(input);

//     // Free the AST (you need to implement this function)
//     return 0;
// }
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
