# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 11:22:27 by lpin              #+#    #+#              #
#    Updated: 2025/08/04 18:18:27 by lpin             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
      ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	  ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	  ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c\
	  ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	  ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	  ft_strjoin_free_s1.c ft_strjoin_free_s2.c ft_destroyer.c ft_split_destroyer.c\
	  get_next_line.c get_next_line_utils.c ft_printf.c ft_printf_utils.c ft_del.c \
	  ft_strcmp.c

BONUS_SRCS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
			 ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

NAME = libft.a

RM = rm -f

HEADER = libft.h get_next_line.h ft_printf.h

%o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $(SRCS)

all: $(NAME) bonus

$(NAME): $(OBJS) $(HEADER)
	@ar rcs $(NAME) $(OBJS)

#ar [opciones] [nombre_archivo_biblioteca] [archivos_objeto]
#ar: crea, modifica y extrae archivos de biblioteca
#r: reemplaza el archivo de la biblioteca si ya existe
#c: crea la biblioteca si no existe
#s: crea un índice de símbolos en la biblioteca

.PHONY: clean fclean bonus re
#.PHONY: indica que clean, fclean y re no son archivos
#que se van a crear, sino que son acciones

bonus: $(BONUS_OBJS) $(HEADER)
	@ar rcs $(NAME) $(BONUS_OBJS)

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "Libft cleaning done."

fclean: clean
	@$(RM) $(NAME)
	@echo "Libft full cleaning done."

re: fclean all
	@echo "Libft rebuild done"
#re: Genera un rebuild del objetivo