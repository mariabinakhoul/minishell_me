/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:04:58 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/04/09 19:04:42 by mabi-nak         ###   ########.fr       */
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
char	*ft_strnstr(char *big,char *little, size_t len);
void	free_ast(t_ast *node);
void	ft_setenv(t_ast *cmd_path);
void	update_env(t_ast *path);
void	**safe_expand_array(void **ptr, size_t old_count, size_t new_count);

#endif