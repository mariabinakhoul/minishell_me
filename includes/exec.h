/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:50:03 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/06/25 17:03:28 by nhaber           ###   ########.fr       */
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
void	freearray(char **array);
int		ft_cd(t_ast *cmd, char ***envp);
int		ft_echo(char **args, char **envp);
int		ft_unset(char **args, char ***envp);
void	ft_env(char **envp);
char	**set_env(char **envp);
char	**sort_array(char **sorted);
t_env	*convert_to_list(char **envp);
char	**convert_to_2d(t_env *head);
t_env	*create_node(t_env *head, char **args);
void	ft_pwd(char **args);
int		ft_exit(char **args);
char	**ft_export(char **args, char **envp);
void	print_export(char **env);
char	*findcommandpath(char *comand, char **envp);
char	*expand_exit_status(int exit_code, char *result);
char	*expand_env_variable(char *arg, int *i, char **env, char *result);
char	*expand_variable(char *arg, t_expand *two_in_one,
			char **env, int exit_code);
char	*expand_home_directory(char *arg, int *i, char **env);
int		is_valid_identifier(char *arg);
int		args_found(t_env *head, char *args);
t_env	*add_new_node(t_env *head, char *arg);
void	update_value(t_env *head, char *args);
char	*get_home_or_oldpwd(t_ast *cmd, char **envp);
void	export_no_params(char **envp);
char	**export_params(char **args, char **env);
int		execute_external(t_ast *cmd, char **envp);
bool	is_builtin(char *cmd);
int		execute_builtin(t_ast *cmd, char ***envp_ptr);
void	replace_env_node_value(t_env *node, char **old_kv, char **new_kv);
int		handle_child_exit(pid_t pid, const char *path, const char *orig_cmd);
int		handle_fork_failure(pid_t pid, const char *path, const char *orig_cmd);
int		handle_redirections(t_ast *cmd_node);
int		handle_heredoc_redirection(t_ast *cmd_node);
char	*try_build_and_access(const char *dir, const char *cmd);
int		handle_exit_unset_export(t_ast *cmd, char ***envp_ptr);

#endif