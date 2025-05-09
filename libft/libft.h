/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:53:51 by mabi-nak          #+#    #+#             */
/*   Updated: 2025/05/09 20:06:00 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <stddef.h>
# include <limits.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				content;
	struct s_list	*next;
	int				index;
}					t_list;
long long int	ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_isdigit(int c);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putstr_fd(char *str, int fd);
int				ft_putstr_fd1(char *str, int fd);
char			**ft_split(char const *str, char c);
char			*ft_strdup(const char *src);
char			*ft_strncpy(char *str, int nb);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *str, int c);
int				ft_printf(const char *str, ...);
int				ft_printf_c(char c);
int				ft_printf_s(char *c);
int				ft_printf_d(int c);
int				ft_printf_u(unsigned int c);
int				ft_printf_p(void *ptr);
int				ft_printf_x(unsigned int ptr);
int				ft_printf__(unsigned int ptr);
int				ft_putchar(char c);
char			*ft_strjoin(char *s1, char const *s2);
int				get_next_line(int fd, char **str);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_bzero(void *s, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strcpy(char *s1, char *s2);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_isalnum(int c);
int				ft_isalpha(int c);

#endif