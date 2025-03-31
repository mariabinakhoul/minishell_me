/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:23:13 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/29 14:27:25 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool is_builtin(char *cmd) {
    char *builtins[] = {"echo", "cd", "pwd", "exit", "env", "unset", "export", NULL};
    for (int i = 0; builtins[i]; i++)
	{
        if (ft_strcmp(cmd, builtins[i]) == 0)
            return true;
    }
    return false;
}

static int	execute_builtin(t_ast *cmd, char **envp_ptr)
{
    printf("%s", *envp_ptr);
	printf("\n=== EXECUTE BUILTIN ===\n");
    printf("Builtin: %s\n", cmd->value);
    printf("Param count: ");
    int count = 0;
    while (cmd->params && cmd->params[count]) count++;
    printf("%d\n", count);

    if (!cmd || !cmd->value)
    {
        printf("Error: Invalid command\n");
        return 1;
    }
    if (ft_strcmp(cmd->value, "cd") == 0)
    {
        printf("Executing cd with %d params\n", count);
        if (count > 1)
        {
            printf("Changing dir to: %s\n", cmd->params[1]);
        }
        else
        {
            printf("Changing to home directory\n");
        }
        ft_cd(cmd, envp_ptr);
        return 0;
    }
    if (ft_strcmp(cmd->value, "env") == 0)
    {
        ft_env(envp_ptr);
    }
	// if (!cmd || !cmd->value)
	// 	return (1);
	// if (ft_strcmp(cmd->value, "echo") == 0)
	// 	return (ft_echo(cmd->params));
	// if (ft_strcmp(cmd->value, "cd") == 0)
	// {
	// 	ft_cd(cmd, envp);
	// 	return (0);
	// }

	// if (ft_strcmp(cmd->value, "pwd") == 0)
	// 	ft_pwd();
	// if (ft_strcmp(cmd->value, "exit") == 0)
		// return (ft_exit(cmd->params));
	// if (ft_strcmp(cmd->value, "env") == 0)
		// return (ft_env(cmd->params));
	// if (ft_strcmp(cmd->value, "unset") == 0)
		// return (ft_unset(cmd->params));
	// if (ft_strcmp(cmd->value, "export") == 0)
		// return (ft_export(cmd->params));
	return (-1);
}


static void execute_external(t_ast *cmd, char **envp) {
    pid_t pid;
    char *path;
    int fd_in, fd_out;

    if (!cmd->params[0]) return;
    path = (access(cmd->params[0], X_OK) == 0) 
           ?  cmd->params[0]
           : findcommandpath(cmd->params[0],envp);
    if (!path) {
        fprintf(stderr, "minishell: %s: command not found\n", cmd->params[0]);
        return;
    }
    pid = fork();
    if (pid == 0) {
        if (cmd->in_file) {
            fd_in = open(cmd->in_file, O_RDONLY);
            if (fd_in == -1)
            {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);  // Replace stdin with the file
            close(fd_in);
        }
        if (cmd->out_file) {
            int flags = O_WRONLY | O_CREAT;
            flags |= (cmd->append) ? O_APPEND : O_TRUNC;
            fd_out = open(cmd->out_file, flags, 0644);
            if (fd_out == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);  // Replace stdout with the file
            close(fd_out);
        }

        // Execute the command
        execve(path, cmd->params, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        waitpid(pid, NULL, 0);  // Wait for child
    } else {
        perror("fork");
    }
    free(path);
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
	char	**all_path;
	char	*finalpath;
	char	*cmdpath;
	int		i;

	findpath(&envp);
	all_path = ft_split(*envp + 5, ':');
	i = 0;
	while (all_path[i])
	{
		finalpath = ft_strjoin(all_path[i], "/");
		cmdpath = ft_strjoin(finalpath, comand);
		free(finalpath);
		if (access(cmdpath, X_OK) == 0)
			return (cmdpath);
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
        printf("  ");  // Indentation for tree structure

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
    {
        printf("PIPE\n");
    }

    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}



void	execute(char *input, char **envp)
{
	t_ast	*ast;

	ast = parse_input(input);

	if (!ast)
		return ;

	execute_command(ast, envp);
	free_ast(ast);
}


int execute_command(t_ast *cmd, char **envp)
{
	printf("\n=== EXECUTE COMMAND ===\n");
    printf("Command: %s\n", cmd->value ? cmd->value : "(null)");
    printf("Params: ");
    if (cmd->params) {
        for (int i = 0; cmd->params[i]; i++) {
            printf("[%s] ", cmd->params[i]);
        }
    }
    printf("\n");
    if (!cmd) {
        printf("Error: Null command\n");
        return 1;
    }
    // Handle pipelines (e.g., cmd1 | cmd2)
    if (cmd->type == PIPE) {
        int pipefd[2];
        pipe(pipefd);
        if (fork() == 0)
        {
			close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);  // cmd1 writes to pipe
            close(pipefd[1]);
            execute_command(cmd->left, envp);
            exit(EXIT_SUCCESS);
        } 
        else
        {
			close (pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);   // cmd2 reads from pipe
            close(pipefd[0]);
            execute_command(cmd->right, envp);
        }
        return 0;
    }
	if (!cmd->value)
	{
		fprintf(stderr, "Error: command is null\n");
		return (1);
	}
    if (is_builtin(cmd->value))
        return execute_builtin(cmd, envp);
    else
        execute_external(cmd, envp);
    return 0;
}