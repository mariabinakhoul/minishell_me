/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:51:21 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/01 12:21:26 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//function helper for single nodes if there's a string to print for example 
// if it sees a single quote it will skip it and it will allocate from the first 
t_chain	*handle_single_quotes(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int		start;
	t_chain	*new_node;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	new_node = create_new_node(TYPE_QUOTE,
			ft_strndup(&str[start], *i - start - 1));
	if (!new_node)
		return (NULL);
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (*head);
}


//function helper that handle double quotes and allocates for everything between the quotes
// handles for error such as if empty
t_chain	*handle_double_quotes(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int		start;
	t_chain	*new_node;

	start = ++(*i);
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] == '"')
		(*i)++;
	new_node = create_new_node(TYPE_DQUOTE, ft_strndup(&str[start], *i - start - 1));
	if (!new_node)
		return (NULL);
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (*head);
}

