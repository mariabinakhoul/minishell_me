/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_dhandler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:37:26 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 17:18:37 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_quoted_string(char *str, int *i, int quote_start)
{
	int		start;
	char	*quoted_part;

	(void)quote_start;
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
	if (quoted_part && quoted_part[0] == '\0')
	{
		free(quoted_part);
		return (NULL);
	}
	return (quoted_part);
}

void	merge_with_current_value(t_chain **current, char *quoted_part, int *i)
{
	char	*merged_value;

	merged_value = ft_strjoin((*current)->value, quoted_part);
	if (!merged_value)
		return ;
	free((*current)->value);
	(*current)->value = merged_value;
	(*current)->end_pos = *i;
	free(quoted_part);
}

t_chain	*handle_double_quotes(char *str, int *i,
		t_chain **head, t_chain **current)
{
	int		quote_start;
	char	*quoted_part;
	t_chain	*new_node;

	quote_start = *i;
	quoted_part = process_quoted_string(str, i, quote_start);
	if (!quoted_part)
		return (NULL);
	if (quoted_part[0] == '\0')
	{
		free(quoted_part);
		return (*head);
	}
	if (*current && ((*current)->end_pos == quote_start))
		merge_with_current_value(current, quoted_part, i);
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
