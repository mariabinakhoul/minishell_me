SRC = ft_atoi.c ft_itoa.c ft_isalpha.c ft_isalnum.c ft_strcpy.c ft_substr.c ft_isdigit.c ft_bzero.c ft_strncmp.c ft_calloc.c ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strdup.c ft_strncpy.c ft_strlen.c ft_strchr.c ft_printf_c.c ft_printf_d.c ft_printf_p.c ft_printf_s.c ft_printf_u.c ft_printf_x.c ft_printf_X.c ft_printf.c get_next_line.c ft_strjoin.c


OBJS = ${SRC:.c=.o}


# SRCS = $(addsuffix .c, ${SRC})


NAME = libft.a

HEAD = libft.h

RN = ranlib

AR = ar rc

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${AR} ${NAME} ${OBJS}
			${RN} ${NAME}


clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re