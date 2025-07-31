# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manualva <manualva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/07 19:58:06 by manualva          #+#    #+#              #
#    Updated: 2025/07/29 09:40:17 by manualva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = parser_tester.c \
       \
       src/parser/cmd_utils.c \
       src/parser/expander.c \
       src/parser/expander_utils.c \
       src/parser/lexer.c \
       src/parser/parser.c \
       src/parser/quotes_utils.c \
       src/parser/syntax_checker.c \
       src/parser/token_utils.c \
       src/parser/redirect.c \
       src/parser/heredoc.c \
       \
       src/signals/status.c \
       src/signals/signals.c \
       \
       src/utils/is_utils.c \
       src/utils/substr_dup.c \
       src/utils/print_error.c \
       src/utils/ft_strcmp.c \
       \
       src/env/mock_env.c \

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilibft

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all