/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:52:47 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/18 15:00:26 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void	sigint_heredoc(int signum)
{
	(void)signum;
	g_exit_code = 130;
	exit(130);
}

ssize_t	get_next_heredoc_line(char **line, size_t *len, int write_fd)
{
	ssize_t	nread;

	write(STDOUT_FILENO, "heredoc> ", 9);
	nread = getline(line, len, stdin);
	if (nread == -1)
	{
		if (errno == EINTR)
		{
			free(*line);
			close(write_fd);
			exit(130);
		}
		perror("getline");
		free(*line);
		close(write_fd);
		exit(EXIT_FAILURE);
	}
	return (nread);
}

char	*ft_heredoc(const char *delimiter, int write_fd, char **env)
{
	char	*line;
	char	*expanded;
	size_t	len;
	ssize_t	nread;

	line = NULL;
	len = 0;
	setup_runtime_signals();
	signal(SIGINT, sigint_heredoc);
	while (1)
	{
		nread = get_next_heredoc_line(&line, &len, write_fd);
		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		if (ft_strcmp(line, (char *)delimiter) == 0)
			break ;
		expanded = expand_argument(line, 0, env, 0);
		write(write_fd, expanded, ft_strlen(expanded));
		write(write_fd, "\n", 1);
		free(expanded);
	}
	setup_runtime_signals();
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
