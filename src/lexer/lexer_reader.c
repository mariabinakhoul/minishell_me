/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:54 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/28 14:30:02 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	add_node_to_list(t_chain **head, t_chain **current, t_chain *new_node)
{
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}

t_chain	*current_node_helper(char *str, int *i,
	t_chain **head, t_chain **current)
{
	int		start;
	t_chain	*new_node;
	t_token	state;
	int		len;
	t_token	op_type;

	state = STATE_ANY;
	start = *i;
	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		len = 1;
		if (str[*i] == '>' && str[*i + 1] == '>')
		{	
			op_type = TYPE_APPEND;
			len = 2;
		}
		else if (str[*i] == '<' && str[*i + 1] == '<')
		{
			op_type = TYPE_HEREDOC;
			len = 2;
		}
		else
			op_type = return_operators_type(str[*i]);
		new_node = create_new_node(op_type, ft_strndup(&str[*i], len));
		if (!new_node)
			return (NULL);
		new_node->start_pos = *i;
		new_node->end_pos = *i + len;
		add_node_to_list(head, current, new_node);
		*i += len;
		return (*head);
	}
	else if (str[*i] == '\'')
		return (handle_single_quotes(str, i, head, current));
	else if (str[*i] == '"')
		return (handle_double_quotes(str, i, head, current));
	else
	{
		start = *i;
        while (str[*i] && set_lexer_type(str[*i]) == TYPE_WORD)
            (*i)++;
        len = *i - start;
        char *word = ft_strndup(&str[start], len);
        if (!word)
            return NULL;

        /* ← if this chunk is immediately contiguous with the previous token, merge it */
        if (*current && (*current)->end_pos == start)
        {
            char *merged = ft_strjoin((*current)->value, word);
            free((*current)->value);
            (*current)->value = merged;
            (*current)->end_pos = *i;
            free(word);
        }
        else
        {
            new_node = create_new_node(TYPE_WORD, word);
            new_node->start_pos = start;
            new_node->end_pos = *i;
            add_node_to_list(head, current, new_node);
        }
	}
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
			current_node_helper(str, &i, &head, &current);
	}
	return (head);
}
