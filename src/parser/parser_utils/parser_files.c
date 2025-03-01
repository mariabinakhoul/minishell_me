/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabi-nak <mabi-nak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:43:34 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/02/27 19:57:32 by mabi-nak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redirect_to_in(t_ast_utils **util)
{
	int	fd;

	if (!(*util)->in)
		return ;
	fd = open ((*util), O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening input file");
		(*util)->exit = 1;
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(fd);
		return ;
	}
	close (fd);
}

void	redirect_to_out(t_ast_utils **filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		perror("Error opening file for output redirection");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return ;
	}
	close(fd);
}


