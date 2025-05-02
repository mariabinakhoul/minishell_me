/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:52:47 by nhaber            #+#    #+#             */
/*   Updated: 2025/05/02 16:41:04 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *ft_heredoc(const char *delimiter, int write_fd)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    // Prompt for heredoc content
    while (1)
    {
        // Print prompt (optional)
        write(STDOUT_FILENO, "heredoc> ", 9);

        // Get the next line of input
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        // Check if the line matches the delimiter
        if (strncmp(line, delimiter, strlen(delimiter)) == 0)
        {
            // If the delimiter is encountered, stop reading
            break;
        }

        // Otherwise, write the content to the pipe
        write(write_fd, line, nread);
    }

    free(line); // Don't forget to free the line buffer
    return NULL;
}

t_ast *handle_heredoc(t_ast *cmd_node, t_chain *token)
{
    t_chain *next_token = token->next;
		if (next_token && (next_token->type == TYPE_WORD || next_token->type == TYPE_QUOTE))
		{
			cmd_node->heredoc = true;
			cmd_node->heredoc_delim = ft_strdup(next_token->value);
		}
		else
		{
			write(2, "bash: syntax error near unexpected token `newline'\n", 52);
			exit_code = 2;
            return NULL;
		}
        return cmd_node;
}