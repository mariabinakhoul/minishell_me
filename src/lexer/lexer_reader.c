/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:54 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/18 15:23:07 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_node_to_list(t_chain **head, t_chain **current, t_chain *new_node)
{
	if (*head == NULL)
		*head = new_node;
	else
		(*current)->next = new_node;
	*current = new_node;
}

void	merge_with_current_node(t_chain **current, char *word, int *i)
{
	char	*merged;

	merged = ft_strjoin((*current)->value, word);
	if (!merged)
		return ;
	free((*current)->value);
	(*current)->value = merged;
	(*current)->end_pos = *i;
	free(word);
}

t_chain	*handle_word_processing(char *str,
	int *i, t_chain **head, t_chain **current)
{
	int		start;
	int		len;
	t_chain	*new_node;
	char	*word;

	start = *i;
	while (str[*i] && set_lexer_type(str[*i]) == TYPE_WORD)
		(*i)++;
	len = *i - start;
	word = ft_strndup(&str[start], len);
	if (!word)
		return (NULL);
	if (*current && (*current)->end_pos == start
		&& (*current)->type == TYPE_WORD)
		merge_with_current_node(current, word, i);
	else
	{
		new_node = create_new_node(TYPE_WORD, word);
		new_node->start_pos = start;
		new_node->end_pos = *i;
		add_node_to_list(head, current, new_node);
	}
	return (*head);
}

t_token	get_operator_type(char *str, int *i, int *len)
{
	t_token	op_type;

	*len = 1;
	if (str[*i] == '>' && str[*i + 1] == '>')
	{
		op_type = TYPE_APPEND;
		*len = 2;
	}
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		op_type = TYPE_HEREDOC;
		*len = 2;
	}
	else
	{
		op_type = return_operators_type(str[*i]);
	}
	return (op_type);
}

t_chain	*current_node_helper(char *str, int *i,
	t_chain **head, t_chain **current)
{
	t_chain	*new_node;
	int		len;
	t_token	op_type;

	if (str[*i] == '>' || str[*i] == '<' || str[*i] == '|')
	{
		len = 1;
		op_type = get_operator_type(str, i, &len);
		new_node = create_new_node(op_type, ft_strndup(&str[*i], len));
		if (!new_node)
			return (NULL);
		new_node->start_pos = *i;
		new_node->end_pos = *i + len;
		add_node_to_list(head, current, new_node);
		*i += len;
	}
	else if (str[*i] == '\'')
		return (handle_single_quotes(str, i, head, current));
	else if (str[*i] == '"')
		return (handle_double_quotes(str, i, head, current));
	else
		return (handle_word_processing(str, i, head, current));
	return (*head);
}
