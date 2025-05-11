/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:04:58 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/10 09:50:26 by nhaber           ###   ########.fr       */
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
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
# include "lexer.h"
# include "tree.h"
# include "exec.h"

extern int exit_code;

char	*ft_strndup(const char *src, int n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
void	*ft_realloc(void *ptr, size_t new_size);
char	*ft_strnstr(char *big, char *little, size_t len);
void	ft_setenv(t_ast *cmd_path);
void	update_env(t_ast *path);
void reset_sig(int signo);
void set_signals();
void def_signals();
int exit_helper(long long int nb);
void ignore_signals();
void	ft_pwd(char **args);
void	**safe_expand_array(void **ptr, size_t old_count, size_t new_count);
void	ft_swap(char **a, char **b);
char	*ft_heredoc(const char *delimiter, int write_fd);
void	free_lexer_nodes(t_chain *head);
void free_2d(char **str);
int costum_atoi(const char *str, long long *out);
void free_ast(t_ast *ast);

#endif