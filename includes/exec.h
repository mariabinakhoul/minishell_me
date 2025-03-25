/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 19:50:03 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/03/25 20:38:08 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

// int	execute_builtin(t_ast *cmd, char **envp);
// void	execute_external(t_ast *cmd, char **envp);
int		execute_command(t_ast *cmd, char **envp);
void	execute(char *input, char **envp);
char	*findcommandpath(char **comand, char **envp);
void	freearray(char **array);
void ft_cd(t_ast *cmd, char **envp_ptr);


#endif