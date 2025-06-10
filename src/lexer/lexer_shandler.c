/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_shandler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:51:21 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/10 21:14:35 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_single_quoted_string(char *str, int *i, int *quote_start)
{
	int		start;
	int		quote_end;
	char	*quoted_part;

	*quote_start = *i;
	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (str[*i] != '\'')
	{
		g_exit_code = 2;
		ft_putstr_fd("unmatched single quotes\n", 2);
		return (NULL);
	}
	quote_end = *i;
	quoted_part = ft_strndup(&str[start], quote_end - start);
	(*i)++;
	if (quoted_part && quoted_part[0] == '\0')
	{
		free(quoted_part);
		return (NULL);
	}
	return (quoted_part);
}

void	merge_with_current_value_and_free(t_chain **current,
	char *quoted_part, int *i)
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

t_chain	*handle_single_quotes(char *str, int *i,
	t_chain **head, t_chain **current)
{
	char	*quoted_part;
	char	*merged_value;
	int		quote_start;
	t_chain	*new_node;

	quoted_part = process_single_quoted_string(str, i, &quote_start);
	if (!quoted_part)
		return (NULL);
	if (quoted_part[0] == '\0')
	{
		free(quoted_part);
		return (*head);
	}
	if (*current && (*current)->end_pos == quote_start)
		merge_with_current_value_and_free(current, quoted_part, i);
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
