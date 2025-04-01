NAME = minishell

HEADER = ./includes

LIBFT = libft/libft.a

READLINE_FLAGS = -lreadline -lhistory

CC = gcc

CFLAGS = -g -I $(HEADER) -Wall -Wextra -Werror

SRCS = lexer/lexer_types lexer/lexer_handler lexer/lexer_reader main utils/utils parser/parser_part2/parser_alpha execution/exec execution/builtins/cd execution/builtins/env execution/builtins/pwd execution/builtins/unset expansion/expansion expansion/expansion_utils execution/builtins/echo

SRC = $(addprefix src/, $(addsuffix .c, $(SRCS)))

SHELL := /bin/bash

COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
NO_COLOR    = \033[m

OBJS = $(addprefix objs/, $(addsuffix .o, $(SRCS)))

all: $(NAME)

objs/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(READLINE_FLAGS)
	@printf "%-53b%b" "$(COM_COLOR)Project Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

$(LIBFT):
	@make -C ./libft
	@printf "%-53b%b" "$(COM_COLOR)LIBFT Compiled:" "$(OK_COLOR)[✓]$(NO_COLOR)\n"

clean:
	rm -rf objs/
	@make clean -C ./libft
	@printf "%-53b%b" "$(COM_COLOR)OBJECT FILES DELETED:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

fclean: clean
	rm -f $(NAME)
	rm -f ./libft/libft.a
	@printf "%-53b%b" "$(COM_COLOR)ALL CLEAN:" "$(ERROR_COLOR)[✓]$(NO_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re

.SILENT: clean fclean re all