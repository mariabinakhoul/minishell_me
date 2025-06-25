/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 15:32:59 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_builtin(char *cmd)
{
	int		i;
	char	*builtins[8];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "exit";
	builtins[4] = "env";
	builtins[5] = "unset";
	builtins[6] = "export";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	execute_builtin_command(t_ast *cmd, char ***envp_ptr)
{
	int		ret;

	ret = 0;
	if (handle_redirections(cmd) != 0)
		ret = 1;
	else if (ft_strcmp(cmd->value, "cd") == 0)
		ret = ft_cd(cmd, envp_ptr);
	else if (ft_strcmp(cmd->value, "env") == 0)
	{
		ft_env(*envp_ptr);
		ret = 0;
	}
	else if (ft_strcmp(cmd->value, "echo") == 0)
		ret = ft_echo(cmd->params, *envp_ptr);
	else if (ft_strcmp(cmd->value, "pwd") == 0)
	{
		ft_pwd(cmd->params);
		ret = 0;
	}
	else
		ret = handle_exit_unset_export(cmd, envp_ptr);
	return (ret);
}

int	execute_builtin(t_ast *cmd, char ***envp_ptr)
{
	int		saved_stdin;
	int		saved_stdout;
	int		ret;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
	{
		perror("dup");
		return (1);
	}
	ret = execute_builtin_command(cmd, envp_ptr);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}

void	run_child_process(t_ast *cmd, const char *path, char **envp)
{
	def_signals();
	if (handle_redirections(cmd) != 0)
		exit(EXIT_FAILURE);
	execve(path, cmd->params, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	execute_external(t_ast *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	if (!cmd->params[0])
		return (1);
	if (access(cmd->params[0], X_OK) == 0)
		path = cmd->params[0];
	else
		path = findcommandpath(cmd->params[0], envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->params[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (127);
	}
	pid = fork();
	if (pid == 0)
		run_child_process(cmd, path, envp);
	else if (pid > 0)
		return (handle_child_exit(pid, path, cmd->params[0]));
	else
		return (handle_fork_failure(pid, path, cmd->params[0]));
	return (EXIT_FAILURE);
}
