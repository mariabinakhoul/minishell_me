/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/29 17:13:59 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int handle_redirections(t_ast *cmd_node)
// {
//     if (cmd_node->out_file)
//     {
//         int fd = open(cmd_node->out_file, O_WRONLY | 
	//O_CREAT | O_TRUNC, 0644);
//         if (fd == -1)
//         {
//             perror("Error opening output file");
//             return -1;
//         }
//         printf("Redirecting output to file: %s\n", cmd_node->out_file);
//         // Redirect stdout to the file
//         if (dup2(fd, STDOUT_FILENO) == -1)
//         {
//             perror("Error duplicating file descriptor");
//             close(fd);
//             return -1;
//         }
//         close(fd);  // Close fd after redirection
//     }

//     return 0;  // Success
// }

int	handle_redirections(t_ast *cmd_node)
{
	int	fd;
	int	flags;
	int	house_pipe[2];

	/* Here-document: create a pipe and read until delimiter */
	if (cmd_node->heredoc)
	{
		if (pipe(house_pipe) == -1)
			return (perror("pipe"), 1);
		/* write end feeds heredoc, read end becomes STDIN */
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
	/* Input redirection (<) */
	if (cmd_node->in_file)
	{
		fd = open(cmd_node->in_file, O_RDONLY);
		if (fd < 0)
			return (perror(cmd_node->in_file), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (perror("dup2 (stdin)"), close(fd), 1);
		close(fd);
	}
	/* Output redirection (>, >>) */
	if (cmd_node->out_file)
	{
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

/**
 * Check if the command is a shell builtin.
 */
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

/**
 * Execute a builtin command in the current process, with redirections applied.
 */
static int	execute_builtin(t_ast *cmd, char ***envp_ptr)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

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
		// char **newenv = ft_export(cmd->params, *envp_ptr);
		// if (newenv)
		// {	
		// 	free_2d(*envp_ptr);
		// 	*envp_ptr = newenv;
		// }
		char **newenv = ft_export(cmd->params, *envp_ptr);
        /* only free/assign if ft_export really gave us a different array */
        if (newenv && newenv != *envp_ptr)
        {
            free_2d(*envp_ptr);
            *envp_ptr = newenv;
        }
		ret = 0;
	}
	else
		ret = 0;

	/* Restore original std fds */
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);

	return (ret);
}

/**
 * Execute an external command by forking and execve.
 */
static int	execute_external(t_ast *cmd, char **envp)
{
	pid_t	pid;
	char	*path;
	int		fd_in;
	int		fd_out;
	int		status;
	int		ret;

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
		if (handle_redirections(cmd) != 0)
			ret = 1;
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
	int		 i;

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

void	print_ast(t_ast *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (node->type == CMD)
	{
		printf("CMD: ");
		for (i = 0; node->params && node->params[i]; i++)
			printf("[%s] ", node->params[i]);
		if (node->in_file)
			printf("(IN: %s) ", node->in_file);
		if (node->out_file)
			printf("(OUT: %s, APPEND: %d) ", node->out_file, node->append);
		printf("\n");
	}
	else if (node->type == PIPE)
		printf("PIPE\n");
	print_ast(node->right, depth + 1);
}

/**
 * Entry point for execution: parse, expand and execute.
 */
// void	execute(char *input, char ***envp)
// {
// 	t_ast *ast;
// 	int exit_code;

// 	exit_code = 0;
// 	ast = parse_input(input);
// 	if (!ast)
// 		return;
// 	expand_tree(ast, *envp, exit_code);
// 	exit_code = execute_command(ast, envp, &exit_code);
// 	free_ast(ast);
// }

/**
 * Dispatch execution based on AST node type.
 */
int	execute_command(t_ast *cmd, char ***envp, int *exit_code)
{
	int pipefd[2];
	pid_t left_pid, right_pid;
	int status_left, status_right;

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
	/* Single command */
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
