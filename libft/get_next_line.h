/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:44:53 by lpin              #+#    #+#             */
/*   Updated: 2024/09/09 16:13:41 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_body
{
	int				fd;
	int				read_size;
	unsigned int	content_size;
	int				offset;
	char			*content;
	char			*ret;
}					t_body;

int				ft_gnl_searcher(const char *haystack);

unsigned int	gnl_strlen(char *s, int i);

unsigned int	ft_gnl_strlcat(char *dst, char *src, unsigned int dstsize);

void			*ft_gnl_destroyer(char **to_destroy);

char			*ft_gnl_put_forward(char *src, int len);

void			ft_gnl_save_content(t_body *body, char *buffer);

int				ft_gnl_read(t_body *body, char *buffer);

void			ft_gnl_resize(t_body *body, char *buffer);

void			ft_gnl_save_ret(t_body *body);

char			*get_next_line(int fd);

#endif