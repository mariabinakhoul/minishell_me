/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/09 17:08:34 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_redirections(t_ast *cmd_node)
{
	int	fd;
	int	flags;
	int	house_pipe[2];

	if (cmd_node->heredoc)
	{
		if (pipe(house_pipe) == -1)
			return (perror("pipe"), 1);
		ft_heredoc(cmd_node->heredoc_delim, house_pipe[1]);
		close(house_pipe[1]);
		if (dup2(house_pipe[0], STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			close(house_pipe[0]);
			return (1);
		}
		close(house_pipe[0]);
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
		printf("HERE\n");
		flags = O_WRONLY | O_CREAT;
		flags |= (cmd_node->append) ? O_APPEND : O_TRUNC;
		fd = open(cmd_node->out_file, flags, 0644);
		if (fd < 0)
			return (perror(cmd_node->out_file), 1);
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (perror("dup2 (stdout)"), close(fd), 1);
		close(fd);
	}
	return (0);
}

static bool	is_builtin(char *cmd)
{
	int		i;
	char	*builtins[] = {"echo", "cd", "pwd", "exit", "env", "unset", "export", NULL};

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}

static int	execute_builtin(t_ast *cmd, char ***envp_ptr)
{
	int		saved_stdin;
	int		saved_stdout;
	int		ret;
	char	**newenv;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
	{
		perror("dup");
		return (1);
	}
	if (handle_redirections(cmd) != 0)
		ret = 1;
	else if (ft_strcmp(cmd->value, "cd") == 0)
		ret = ft_cd(cmd, *envp_ptr);
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
	else if (ft_strcmp(cmd->value, "exit") == 0)
		ret = ft_exit(cmd->params);
	else if (ft_strcmp(cmd->value, "unset") == 0)
		ret = ft_unset(cmd->params, envp_ptr);
	else if (ft_strcmp(cmd->value, "export") == 0)
	{
		newenv = ft_export(cmd->params, *envp_ptr);
		if (newenv && newenv != *envp_ptr)
		{
			free_2d(*envp_ptr);
			*envp_ptr = newenv;
		}
		ret = 0;
	}
	else
		ret = 0;
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (ret);
}

static int	execute_external(t_ast *cmd, char **envp)
{
	pid_t	pid;
	char	*path;
	int		fd_in;
	int		fd_out;
	int		status;
	// int		ret;

	if (!cmd->params[0])
		return (1);
	path = (access(cmd->params[0], X_OK) == 0)
		? cmd->params[0]
		: findcommandpath(cmd->params[0], envp);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd->params[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		def_signals();
		// if (handle_redirections(cmd) != 0)
		// 	ret = 1;
		execve(path, cmd->params, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		ignore_signals();
		waitpid(pid, &status, 0);
		if (path != cmd->params[0])
			free(path);
		set_signals();
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (128 + WTERMSIG(status));
	}
	else
	{
		ignore_signals();
		waitpid(pid, &status, 0);
		set_signals();
		perror("fork");
		if (path != cmd->params[0])
			free(path);
		return (-1);
	}
}

void	findpath(char ***envp)
{
	while (**envp)
	{
		if (ft_strnstr(**envp, "PATH=", 5))
			return ;
		(*envp)++;
	}
}

char	*findcommandpath(char *comand, char **envp)
{
	char	**envp_copy;
	char	**all_path;
	char	*finalpath;
	char	*cmdpath;
	int		i;

	envp_copy = envp;
	while (*envp_copy && !ft_strnstr(*envp_copy, "PATH=", 5))
		envp_copy++;
	if (!*envp_copy)
		return (NULL);
	all_path = ft_split(*envp_copy + 5, ':');
	i = 0;
	while (all_path[i])
	{
		finalpath = ft_strjoin(all_path[i], "/");
		cmdpath = ft_strjoin(finalpath, comand);
		free(finalpath);
		if (access(cmdpath, X_OK) == 0)
		{
			freearray(all_path);
			return (cmdpath);
		}
		free(cmdpath);
		i++;
	}
	freearray(all_path);
	return (NULL);
}

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


int	execute_command(t_ast *cmd, char ***envp, int *exit_code)
{
	int		pipefd[2];
	pid_t	left_pid;
	pid_t	right_pid;
	int		status_left;
	int		status_right;

	set_signals();
	if (!cmd)
	{
		fprintf(stderr, "Error: Null command\n");
		*exit_code = 1;
		return (1);
	}
	if (cmd->type == PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			*exit_code = 1;
			return (1);
		}
		if (handle_left_pid(cmd, envp, exit_code, pipefd))
			return (1);
		if (handle_right_pid(cmd, envp, exit_code, pipefd))
			return (1);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(left_pid, &status_left, 0);
		waitpid(right_pid, &status_right, 0);
		if (WIFEXITED(status_right))
			*exit_code = WEXITSTATUS(status_right);
		else
			*exit_code = 1;
		return (*exit_code);
	}
	if (!cmd->value)
	{
		fprintf(stderr, "Error: command is null\n");
		*exit_code = 1;
		return (1);
	}
	if (is_builtin(cmd->value))
		*exit_code = execute_builtin(cmd, envp);
	else
		*exit_code = execute_external(cmd, *envp);
	return (*exit_code);
}
