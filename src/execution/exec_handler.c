/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:41:00 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/17 16:14:17 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_output_redirection(const char *path, bool append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(path, flags, 0644);
	if (fd < 0)
	{
		perror(path);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 (stdout)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc_redirection(t_ast *cmd_node)
{
	if (dup2(cmd_node->here_doc_in, STDIN_FILENO) == -1)
	{
		perror("dup2 heredoc");
		close(cmd_node->here_doc_in);
		return (1);
	}
	close(cmd_node->here_doc_in);
	return (0);
}

int	handle_redirections(t_ast *cmd_node)
{
	int	fd;

	if (cmd_node->heredoc && cmd_node->here_doc_in != -1)
	{
		dup2(cmd_node->here_doc_in, STDIN_FILENO);
		close(cmd_node->here_doc_in);
	}
	else if (cmd_node->in_file)
	{
		fd = open(cmd_node->in_file, O_RDONLY);
		if (fd < 0)
			return (perror(cmd_node->in_file), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2 (stdin)"), close(fd), 1);
		close(fd);
	}
	if (cmd_node->out_file)
	{
		if (handle_output_redirection(cmd_node->out_file,
				cmd_node->append))
			return (1);
	}
	return (0);
}

int	handle_fork_failure(pid_t pid, const char *path, const char *orig_cmd)
{
	int	status;

	ignore_signals();
	waitpid(pid, &status, 0);
	set_signals();
	perror("fork");
	if (path != orig_cmd)
		free((void *)path);
	return (-1);
}

int	handle_child_exit(pid_t pid, const char *path, const char *orig_cmd)
{
	int	status;

	ignore_signals();
	waitpid(pid, &status, 0);
	if (path != orig_cmd)
		free ((void *)path);
	set_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (128 + WTERMSIG(status));
}
