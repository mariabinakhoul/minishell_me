/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:41:22 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/18 17:22:50 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_left_pid(t_ast *cmd, char ***envp, int *exit_code, int *pipefd)
{
	pid_t	left_pid;

	left_pid = fork();
	if (left_pid == 0)
	{
		set_signals();
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exit(execute_command(cmd->left, envp, exit_code));
	}
	else if (left_pid < 0)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		*exit_code = 1;
		return (1);
	}
	return (0);
}

int	handle_right_pid(t_ast *cmd, char ***envp, int *exit_code, int *pipefd)
{
	pid_t	right_pid;

	right_pid = fork();
	if (right_pid == 0)
	{
		set_signals();
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		exit(execute_command(cmd->right, envp, exit_code));
	}
	else if (right_pid < 0)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		*exit_code = 1;
		return (1);
	}
	return (0);
}

int	handle_pipeline_execution(t_ast *cmd, char ***envp,
	int *exit_code, int *pipefd)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		status_left;
	int		status_right;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		*exit_code = 1;
		return (1);
	}
	left_pid = handle_left_pid(cmd, envp, exit_code, pipefd);
	if (left_pid == -1)
		return (1);
	right_pid = handle_right_pid(cmd, envp, exit_code, pipefd);
	if (right_pid == -1)
		return (1);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(left_pid, &status_left, 0);
	waitpid(right_pid, &status_right, 0);
	if (WIFEXITED(status_right))
		return (WEXITSTATUS(status_right));
	else
		return (1);
}

int	handle_command_errors_and_pipeline(t_ast *cmd, char ***envp,
	int *exit_code, int *pipefd)
{
	if (!cmd)
	{
		ft_putstr_fd("Error: Null command\n", 2);
		*exit_code = 1;
		return (1);
	}
	if (cmd->type == PIPE)
	{
		if (handle_pipeline_execution(cmd, envp, exit_code, pipefd))
			return (1);
		return (*exit_code);
	}
	if (!cmd->value)
	{
		ft_putstr_fd("Error: command is null\n", 2);
		*exit_code = 1;
		return (1);
	}
	return (0);
}

int	execute_command(t_ast *cmd, char ***envp, int *exit_code)
{
	int		pipefd[2];

	set_signals();
	if (cmd->type == PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			*exit_code = 1;
			return (1);
		}
		if (handle_pipeline_execution(cmd, envp, exit_code, pipefd))
			return (1);
		return (*exit_code);
	}
	if (is_builtin(cmd->value))
		*exit_code = execute_builtin(cmd, envp);
	else
		*exit_code = execute_external(cmd, *envp);
	return (*exit_code);
}
