/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:50:03 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/19 10:42:18 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}t_env;

int		execute_command(t_ast *cmd, char ***envp, int *exit_code);
void	execute(char *input, char ***envp);
void	freearray(char **array);
int		ft_cd(t_ast *cmd, char **envp_ptr);
int		ft_echo(char **args, char **envp);
int		ft_unset(char **args, char ***envp);
void print_env(t_env *head);
void	ft_env(char **envp);
char **set_env(char **envp);
char **sort_array(char **sorted);
t_env *convert_to_list(char **envp);
char **convert_to_2d(t_env *head);
t_env *create_node(t_env *head,char **args);
void print2d(char **array);
void	ft_pwd(char **args);
int		ft_exit(char **args);
t_env	*clone_env(char **envp);
char	**ft_export(char **args, char **envp); //not returning the new env so it is not getting updated
void print_export(char **env);
char	*findcommandpath(char *comand, char **envp);
void	findpath(char ***envp);
char	*expand_exit_status(int exit_code, char *result);
char	*expand_env_variable(char *arg, int *i, char **env, char *result);
char	*expand_variable(char *arg, int *i,
			char **env, int exit_code, char *result);
char	*expand_home_directory(char *arg, int *i, char **env, char *result);
int		is_valid_identifier(char *arg);


#endif