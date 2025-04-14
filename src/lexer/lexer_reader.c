/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:54 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/12 10:31:38 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//creates new nodes/ token to add to the chain and
// will give them the given type ad value
t_chain	*create_new_node(t_token type, char *value)
{
	t_chain	*new_node;

	new_node = malloc(sizeof(t_chain));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

static t_token	handle_operator(char *str, int *i)
{
	t_token	state;

	state = STATE_ANY;
	if ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<'))
	{
		if (str[*i] == '>')
			state = TYPE_APPEND;
		else
			state = TYPE_HEREDOC;
		(*i) += 2;
	}
	else
	{
		state = set_lexer_type(str[*i]);
		(*i)++;
	}
	return (state);
}

void	add_node_to_list(t_chain **head, t_chain **current, t_chain *new_node)
{
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}

//allocates everything by calling create new node
//it identify the  heredoc and append and tokenize them together
//returns the "chain" in the correct order 
// also finds the type of each argument find them in enum or lexer_types.c
t_chain	*current_node_helper(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int		start;
	t_chain	*new_node;
	t_token	state;

	state = STATE_ANY;
	start = *i;
	if (return_operators_type(str[*i]))
		handle_operator(str, i);
	else if (str[*i] == '\'')
		return (handle_single_quotes(str, i, head, current));
	else if (str[*i] == '"')
		return (handle_double_quotes(str, i, head, current));
	else
	{
		while (str[*i] && set_lexer_type(str[*i]) == TYPE_WORD)
			(*i)++;
		state = TYPE_WORD;
	}
	new_node = create_new_node(state, ft_strndup(&str[start], *i - start));
	if (!new_node)
		return (NULL);
	new_node->start_pos = start;
	new_node->end_pos = *i;
	add_node_to_list(head, current, new_node);
	return (*head);
}

//it checks for the type and call the helper function to tokenize and 
// allocate perfectly anything written
t_chain	*lexer_filler(char *str)
{
	int		i;
	t_chain	*head;
	t_chain	*current;

	head = NULL;
	current = NULL;
	i = 0;
	while (str[i])
	{
		while (set_lexer_type(str[i]) == TYPE_SPACE
			|| set_lexer_type(str[i]) == TYPE_TAB)
			i++;
		if (str[i])
			head = current_node_helper(str, &i, &head, &current);
	}
	return (head);
}
