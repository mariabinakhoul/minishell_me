/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:50:03 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/15 22:34:42 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}t_env;

int		execute_command(t_ast *cmd, char **envp, int *last_status);
void	execute(char *input, char **envp);
void	freearray(char **array);
void	ft_cd(t_ast *cmd, char **envp_ptr);
int		ft_echo(char **args, char **envp);
int		ft_unset(char **args, char ***envp);
void	ft_env(char **envp);
void	ft_pwd(void);
int		ft_exit(char **args);
t_env	*clone_env(char **envp);
int	ft_export(char **args, char **envp);
char	*findcommandpath(char *comand, char **envp);
void	findpath(char ***envp);
char	*expand_exit_status(int last_status, char *result);
char	*expand_env_variable(char *arg, int *i, char **env, char *result);
char	*expand_variable(char *arg, int *i,
			char **env, int last_status, char *result);
char	*expand_home_directory(char *arg, int *i, char **env, char *result);

#endif