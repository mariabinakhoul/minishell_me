/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:04:58 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/06 22:11:29 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "lexer.h"
# include "tree.h"
# include "exec.h"

char	*ft_strndup(const char *src, int n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
void	*ft_realloc(void *ptr, size_t new_size);
void	findpath(char ***envp);
char	*ft_strnstr(char *big,char *little, size_t len);
char	*findcommandpath(char *comand, char **envp);
void    free_ast(t_ast *node);
void ft_setenv(t_ast *cmd_path);
void update_env(t_ast *path);
char *ft_get_oldpwd();
char **sort_envp(char **envp);
void print_export(char **envp);
void ft_export(char **envp);
t_env *clone_env(char **envp);
void ft_env(char **envp);
void ft_pwd();

#endif