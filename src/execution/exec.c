/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/19 18:54:22 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int handle_redirections(t_ast *cmd_node)
// {
//     if (cmd_node->out_file)
//     {
//         int fd = open(cmd_node->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

	if (cmd_node->in_file)
	{
		fd = open(cmd_node->in_file, O_RDONLY);
		if (fd == -1)
		{
			perror(cmd_node->in_file);
			return 1;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 (stdin)");
			close(fd);
			return 1;
		}
		close(fd);
	}
	if (cmd_node->out_file)
	{
		int flags = O_WRONLY | O_CREAT;
		flags |= (cmd_node->append) ? O_APPEND : O_TRUNC;
		fd = open(cmd_node->out_file, flags, 0644);
		if (fd == -1)
		{
			perror(cmd_node->out_file);
			return 1;
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 (stdout)");
			close(fd);
			return 1;
		}
		close(fd);
	}

	return (0);
}


static bool	is_builtin(char *cmd)
{
	int		i;
	char	*builtins[8];

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "exit";
	builtins[4] = "env";
	builtins[5] = "unset";
	builtins[6] = "export";
	builtins[7] = NULL;
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
	int	count;

	count = 0;
	if (handle_redirections(cmd) != 0)
	{
		printf("Redirection failed\n");
		return 1;
	}
	while (cmd->params && cmd->params[count])
		count++;
	if (!cmd || !cmd->value)
	{
		printf("Error: Invalid command\n");
		return (1);
	}
	if (ft_strcmp(cmd->value, "cd") == 0)
		return(ft_cd(cmd, *envp_ptr));
	if (ft_strcmp(cmd->value, "env") == 0)
		ft_env(*envp_ptr);
	if (ft_strcmp(cmd->value, "echo") == 0)
		return (ft_echo(cmd->params, *envp_ptr));
	if (ft_strcmp(cmd->value, "pwd") == 0)
		ft_pwd(cmd->params);
	if (ft_strcmp(cmd->value, "exit") == 0)
		return (ft_exit(cmd->params));
	if (ft_strcmp(cmd->value, "unset") == 0)
		return (ft_unset(cmd->params, envp_ptr));
	if (ft_strcmp(cmd->value, "export") == 0)
		// *envp_ptr = ft_export(cmd->params, *envp_ptr);
	{
	char **result = ft_export(cmd->params, *envp_ptr);
	if (result != *envp_ptr)
		*envp_ptr = result;
	
	// Return exit code based on validation
	int i = 1;
	while (cmd->params[i])
	{
		if (!is_valid_identifier(cmd->params[i]))
			return (1);
		i++;
	}
	return (0);
}
	return (0);
}


static int	execute_external(t_ast *cmd, char **envp)
{
	pid_t	pid;
	char	*path;
	int		fd_in;
	int		fd_out;
	int		status;

	if (!cmd->params[0])
		return (1);
	path = (access(cmd->params[0], X_OK) == 0) 
			?  cmd->params[0]
			: findcommandpath(cmd->params[0],envp);
	if (!path)
	{
		fprintf(stderr, "minishell: %s: command not found\n", cmd->params[0]);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		def_signals();
		if (cmd->out_file)
		{
            int flags = O_WRONLY | O_CREAT;
			flags |= (cmd->append) ? O_APPEND : O_TRUNC;
			fd_out = open(cmd->out_file, flags, 0644);
			if (fd_out == -1)
			{
                perror("open");
				exit(EXIT_FAILURE);
			}
		}
        // if (cmd->heredoc)
        // {
        //     int pipefd[2];
        //     if (pipe(pipefd) == -1)
        //     {
        //         perror("pipe");
        //         exit(EXIT_FAILURE);
        //     }

        //     ft_heredoc(cmd->heredoc_delim, pipefd[1]); // write to pipe
        //     close(pipefd[1]); // close write end
        //     dup2(pipefd[0], STDIN_FILENO); // replace stdin with read end
        //     close(pipefd[0]); // close read end, it's now stdin
        // }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
		execve(path, cmd->params, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
    {
        ignore_signals();
        waitpid(pid, &status, 0);
        free(path);
        set_signals();
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        else
            return (128 + WTERMSIG(status));	
    }   
	else
	{
        perror("fork");
		free(path);
		return (-1);
	}
}

void	findpath(char ***envp)
{
	while (**envp != NULL)
	{
		if (ft_strnstr(**envp, "PATH=", 5) != NULL)
			return ;
		(*envp)++;
	}
}

char	*findcommandpath(char *comand, char **envp)
{
    char    **envp_copy = envp;
	char	**all_path;
	char	*finalpath;
	char	*cmdpath;
	int		i;

    while (*envp_copy != NULL)
    {
        if (ft_strnstr(*envp_copy, "PATH=", 5) != NULL)
            break;
        envp_copy++;
    }
    if (*envp_copy == NULL)
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

void print_ast(t_ast *node, int depth)
{
    if (!node)
        return;
    for (int i = 0; i < depth; i++)
        printf("  ");
    if (node->type == CMD)
    {
        printf("CMD: ");
        for (int i = 0; node->params && node->params[i]; i++)
            printf("[%s] ", node->params[i]);
        if (node->in_file)
            printf("(IN: %s) ", node->in_file);
        if (node->out_file)
            printf("(OUT: %s, APPEND: %d) ", node->out_file, node->append);
        printf("\n");
    }
    else if (node->type == PIPE)
        printf("PIPE\n");
    // print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}



void	execute(char *input, char ***envp)
{
    t_ast *ast;
    int exit_code = 0;

    ast = parse_input(input);
    if (!ast)
        return;
    expand_tree(ast, *envp, exit_code);
    exit_code = execute_command(ast, envp, &exit_code);
    free_ast(ast);
}


int execute_command(t_ast *cmd, char ***envp, int *exit_code)
{
    int pipefd[2];
    pid_t left_pid, right_pid;
    int status_left, status_right;

    set_signals();
    if (!cmd)
    {
        fprintf(stderr, "Error: Null command\n");
        *exit_code = 1;
        return 1;
    }
    if (cmd->type == PIPE)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            *exit_code = 1;
            return 1;
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
            return 1;
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
            return 1;
        }
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(left_pid, &status_left, 0);
        waitpid(right_pid, &status_right, 0);
        if (WIFEXITED(status_right))
            *exit_code = WEXITSTATUS(status_right);
        else
            *exit_code = 1;

        return *exit_code;
    }
    if (!cmd->value) 
    {
        fprintf(stderr, "Error: command is null\n");
        *exit_code = 1;
        return 1;
    }
    if (is_builtin(cmd->value))
        *exit_code = execute_builtin(cmd, envp);
    else
        *exit_code = execute_external(cmd, *envp);
    return *exit_code;
}
