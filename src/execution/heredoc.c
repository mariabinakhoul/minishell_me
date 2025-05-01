/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:52:47 by nhaber            #+#    #+#             */
/*   Updated: 2025/04/30 13:14:58 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void ft_heredoc()
// {
//     int fd = open("tmp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//         return ;
//     const char *text = "Hello from low-level I/O!\n";
//     ssize_t bytes_written = write(fd, text, 26);  // 26 is length of string    
//     if (bytes_written == -1)
//     {
//         perror("write");
//             close(fd);
//             return 1;
//         }
    
//         close(fd);  // Always close the file descriptor
//         return 0;
// }