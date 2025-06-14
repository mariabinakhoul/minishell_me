/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:52:47 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/12 11:53:31 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char	*ft_heredoc(const char *delimiter, int write_fd)
{
	char	*line;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
		if (strncmp(line, delimiter, strlen(delimiter)) == 0)
			break ;
		write(write_fd, line, nread);
	}
	free(line);
	return (NULL);
}

t_ast	*handle_heredoc(t_ast *cmd_node, t_chain *token)
{
	t_chain	*next_token;

	next_token = token->next;
	if (next_token && (next_token->type == TYPE_WORD
			|| next_token->type == TYPE_QUOTE))
	{
		cmd_node->heredoc = true;
		cmd_node->heredoc_delim = ft_strdup(next_token->value);
	}
	else
	{
		write(2, "bash: syntax error near unexpected token `newline'\n", 52);
		g_exit_code = 2;
		return (NULL);
	}
	return (cmd_node);
}
