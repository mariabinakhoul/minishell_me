/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:51:21 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/16 10:40:47 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//function helper for single nodes if there's a string to print for example 
// if it sees a single quote it will skip it and it will allocate
//from the first 
// t_chain	*handle_single_quotes(char *str, int *i,
// 		t_chain **head, t_chain **current)
// {
// 	int		start;
// 	t_chain	*new_node;
// 	char	*quoted_part;
// 	char *merged_value;

// 	start = ++(*i);
// 	while (str[*i] && str[*i] != '\'')
// 		(*i)++;
// 	// if (str[*i] == '\'')
// 	// 	(*i)++;
// 	if (str[*i] != '\'')
// 	{
// 		printf("unmatched single quotes\n");
// 		return (NULL);
// 	}
// 	// if (*i - start > 0)
// 	// 	new_node = create_new_node(TYPE_QUOTE,
// 	// 			ft_strndup(&str[start], *i - start - 1));
// 	// else
// 	// 	new_node = create_new_node(TYPE_QUOTE, ft_strdup(""));
// 	// if (!new_node)
// 	// 	return (NULL);
// 	quoted_part = ft_strndup(&str[start], *i - start);
// 	(*i)++;
// 	if (*current && (*current)->type == TYPE_WORD)
//     {
//         merged_value = ft_strjoin((*current)->value, quoted_part);
//         free((*current)->value);
//         (*current)->value = merged_value;
//         free(quoted_part);
//     }
//     else
//     {
//         // Create a new token for this quoted part
//         t_chain *new_node = create_new_node(TYPE_QUOTE, quoted_part);
//         add_node_to_list(head, current, new_node);
//     }
// 	// new_node = create_new_node(TYPE_QUOTE, ft_strndup(&str[start], *i - start - 1));
// 	// add_node_to_list(head, current, new_node);
// 	return (*head);
// }

t_chain *handle_single_quotes(char *str, int *i, t_chain **head, t_chain **current)
{
    int start;
    char *quoted_part;
    char *merged_value;

    // The current character is the opening quote; record its position.
    int quote_start = *i;  
    start = ++(*i);  // start of the content

    while (str[*i] && str[*i] != '\'')
        (*i)++;
    if (str[*i] != '\'')
    {
        exit_code = 2;
        printf("unmatched single quotes\n");
        return (NULL);
    }
    int quote_end = *i;  // position of the closing quote
    quoted_part = ft_strndup(&str[start], quote_end - start);
    (*i)++;  // move past the closing quote

    // Check if the quoted part is directly adjacent to the previous token:
    if (*current && (*current)->end_pos == quote_start)
    {
        // They are adjacent—merge without inserting a space.
        merged_value = ft_strjoin((*current)->value, quoted_part);
        free((*current)->value);
        (*current)->value = merged_value;
        // Update the current token's end position with the closing quote's position.
        (*current)->end_pos = *i;
        free(quoted_part);
    }
    else
    {
        // Not adjacent: create a new token.
        t_chain *new_node = create_new_node(TYPE_QUOTE, quoted_part);
        new_node->quote = 1;          // mark as single-quoted
        new_node->start_pos = quote_start;
        new_node->end_pos = *i;
        add_node_to_list(head, current, new_node);
    }
    return (*head);
}


//function helper that handle double quotes and allocates
//for everything between the quotes
// handles for error such as if empty
t_chain	*handle_double_quotes(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int     start;
    int     quote_start;
    char    *quoted_part;
    char    *merged_value;

    // Record the position of the opening double quote.
    quote_start = *i;
    // Set start to the character immediately after the opening quote.
    start = ++(*i);
    while (str[*i] && str[*i] != '"')
        (*i)++;
    if (str[*i] != '"')
    {
        printf("unmatched double quotes\n");
        return (NULL);
    }
    // Extract the content inside the double quotes.
    quoted_part = ft_strndup(&str[start], *i - start);
    (*i)++;  // Skip the closing double quote.
    
    // Merge with the previous token if it's immediately adjacent.
    // That is, if the previous token’s end position equals the position of the opening quote.
    if (*current && ((*current)->end_pos == quote_start))
    {
        merged_value = ft_strjoin((*current)->value, quoted_part);
        free((*current)->value);
        (*current)->value = merged_value;
        // Update the previous token’s end position to the current pointer.
        (*current)->end_pos = *i;
        free(quoted_part);
    }
    else
    {
        // Otherwise, create a new token for this double-quoted segment.
        t_chain *new_node = create_new_node(TYPE_DQUOTE, quoted_part);
        new_node->quote = 2;        // Mark as double-quoted.
        new_node->start_pos = quote_start;
        new_node->end_pos = *i;
        add_node_to_list(head, current, new_node);
    }
    return (*head);
}
