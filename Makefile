# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 19:58:06 by manualva          #+#    #+#              #
#    Updated: 2025/09/03 18:34:15 by lpin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = parser_tester.c \
	\
	src/env/default_env.c \
	src/parser/cmd_utils.c \
	src/parser/expander.c \
	src/parser/syntax_checker.c \
	src/parser/syntax_utils.c \
	src/parser/token_utils.c \
	src/parser/redirect.c \
	src/parser/redirect_utils.c \
	src/parser/heredoc.c \
	src/parser/lexer.c \
	src/parser/parser.c \
	src/parser/quotes_utils.c \
	src/signals/status.c \
	src/signals/signals.c \
	src/parser/expander_utils.c\
	src/utils/is_utils.c \
	src/utils/substr_dup.c \
	src/utils/print_error.c \
	src/utils/export_utils.c \
	src/utils/lst_utils.c \
	src/utils/env_utils.c \
	src/utils/cd_utils.c \
	src/utils/builtins_utils.c \
	src/utils/cmd_path_utils.c \
	src/utils/multiple_cmds_utils.c \
	src/builtins/cd.c \
	src/builtins/echo.c \
	src/builtins/env.c \
	src/builtins/export.c \
	src/builtins/pwd.c \
	src/builtins/unset.c \
	src/builtins/exit.c \
	src/exec/cmd_path.c \
	src/exec/exec.c \
	src/exec/pipe_utils.c \
	src/exec/single_cmd.c \
	src/exec/multiple_cmds.c \


OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -fsanitize=address -g -Wall -Wextra -Werror -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -ltermcap -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all