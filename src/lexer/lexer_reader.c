/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:54 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/14 16:22:21 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_chain	*current_node_helper(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int		start;
	t_chain	*new_node;
	t_token	state;

	state = STATE_ANY;
	start = *i;
	if (return_operators_type(str[*i]))
	{
		if ((str[*i] == '>' && str[*i + 1] == '>')
			|| (str[*i] == '<' && str[*i + 1] == '<'))
		{
			state = (str[*i] == '>') ? TYPE_APPEND : TYPE_HEREDOC;
			(*i) += 2;
		}
		else
		{
			state = set_lexer_type(str[*i]);
			(*i)++;
		}
	}
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
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
	return (*head);
}

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
