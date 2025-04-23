/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:51:21 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/23 19:03:27 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

t_chain	*handle_single_quotes(char *str, int *i,
	t_chain **head, t_chain **current)
{
	int		start;
	char	*quoted_part;
	char	*merged_value;
	int		quote_start;
	t_chain	*new_node;
	int		quote_end;

	quote_start = *i;
	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] != '\'')
	{
		exit_code = 2;
		printf("unmatched single quotes\n");
		return (NULL);
	}
	quote_end = *i;
	quoted_part = ft_strndup(&str[start], quote_end - start);
	(*i)++;
	if (quoted_part && quoted_part[0] == '\0')  // If the quoted part is empty, do nothing
	{
		free(quoted_part);
		return *head;  // Skip empty quoted part
	}
	if (*current && (*current)->end_pos == quote_start)
	{
		merged_value = ft_strjoin((*current)->value, quoted_part);
		free((*current)->value);
		(*current)->value = merged_value;
		(*current)->end_pos = *i;
		free(quoted_part);
	}
	else
	{
		new_node = create_new_node(TYPE_QUOTE, quoted_part);
		new_node->quote = 1;
		new_node->start_pos = quote_start;
		new_node->end_pos = *i;
		add_node_to_list(head, current, new_node);
	}
	return (*head);
}

t_chain	*handle_double_quotes(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int		start;
	int		quote_start;
	char	*quoted_part;
	char	*merged_value;
	t_chain	*new_node;

	quote_start = *i;
	start = ++(*i);
	while (str[*i] && str[*i] != '"')
		(*i)++;
	if (str[*i] != '"')
	{
		printf("unmatched double quotes\n");
		return (NULL);
	}
	quoted_part = ft_strndup(&str[start], *i - start);
	(*i)++;
	if (quoted_part && quoted_part[0] == '\0')  // If the quoted part is empty, do nothing
	{
		free(quoted_part);
		return *head;  // Skip empty quoted part
	}
	if (*current && ((*current)->end_pos == quote_start))
	{
		merged_value = ft_strjoin((*current)->value, quoted_part);
		free((*current)->value);
		(*current)->value = merged_value;
		(*current)->end_pos = *i;
		free(quoted_part);
	}
	else
	{
		new_node = create_new_node(TYPE_DQUOTE, quoted_part);
		new_node->quote = 2;
		new_node->start_pos = quote_start;
		new_node->end_pos = *i;
		add_node_to_list(head, current, new_node);
	}
	return (*head);
}
