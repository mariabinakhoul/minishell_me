/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:36:47 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/11 14:00:27 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes

void print_list(t_chain *list) {
    while (list) {
        printf("Type: %d, Value: %s\n", list->type, list->value);
        list = list->next;
    }
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    // Calculate total length for concatenation
    int total_length = 0;
    for (int i = 1; i < argc; i++) {
        total_length += strlen(argv[i]) + 1; // +1 for space or null terminator
    }

    // Allocate and concatenate arguments
    char *input = malloc(total_length);
    if (!input) return 1;
    input[0] = '\0';

    for (int i = 1; i < argc; i++) {
        strcat(input, argv[i]);
        if (i < argc - 1) strcat(input, " ");
    }

    t_chain *list = lexer_filler(input);

    print_list(list);

    // Free memory
    t_chain *temp;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->value);
        free(temp);
    }
    free(input);

    return 0;
}

