/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:05:06 by lpin              #+#    #+#             */
/*   Updated: 2024/09/23 20:30:54 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

int	ft_gnl_read(t_body *body, char *buffer)
{
	body->read_size = 1;
	body->offset = 0;
	while (body->offset == 0 && body->read_size > 0)
	{
		buffer[BUFFER_SIZE] = '\0';
		body->read_size = read(body->fd, buffer, BUFFER_SIZE);
		if (body->read_size > 0)
			ft_gnl_save_content(body, buffer);
		body->offset = ft_gnl_searcher(body->content);
	}
	if (body->read_size == 0 && body->offset == -1)
		return (1);
	else if (body->read_size == -1)
		return (-1);
	else
		return (0);
}

void	ft_gnl_resize(t_body *body, char *buffer)
{
	char	*temp;

	body->content_size = gnl_strlen(body->content, -1) + body->read_size;
	temp = ft_calloc(sizeof(char), (gnl_strlen(body->content, -1) + 1));
	if (temp == NULL)
		return ;
	gnl_strlen(temp, gnl_strlen(body->content, -1));
	ft_gnl_strlcat(temp, body->content, (gnl_strlen(body->content, -1) + 1));
	ft_gnl_destroyer(&body->content);
	body->content = ft_calloc(sizeof(char), (body->content_size + 1));
	if (body->content == NULL)
		return ;
	gnl_strlen(body->content, body->content_size);
	ft_gnl_strlcat(body->content, temp, gnl_strlen(temp, -1) + 1);
	ft_gnl_strlcat(body->content, buffer, body->content_size + 1);
	ft_gnl_destroyer(&temp);
}

void	ft_gnl_save_ret(t_body *body)
{
	if (body->content == NULL)
	{
		body->ret = NULL;
		return ;
	}
	if (body->offset == 0)
	{
		body->ret = ft_calloc (sizeof(char), gnl_strlen(body->content, -1) + 1);
		if (body->ret == NULL)
			return ;
		gnl_strlen(body->ret, gnl_strlen(body->content, -1));
		ft_gnl_strlcat(body->ret, body->content,
			(gnl_strlen(body->content, -1) + 1));
		ft_gnl_put_forward(body->content, (gnl_strlen(body->content, -1) + 1));
	}
	else if (body->offset != 0)
	{
		body->ret = ft_calloc (sizeof(char), body->offset + 1);
		if (body->ret == NULL)
			return ;
		gnl_strlen(body->ret, body->offset);
		ft_gnl_strlcat(body->ret, body->content, (body->offset + 1));
		ft_gnl_put_forward(body->content, body->offset);
	}
	body->offset = ft_gnl_searcher(body->content);
}

void	ft_gnl_save_content(t_body *body, char *buffer)
{
	if (*buffer == '\0')
		return ;
	if (body->content == NULL)
	{
		body->content = ft_calloc((body->read_size + 1), sizeof(char));
		if (body->content == NULL)
			return ;
		gnl_strlen(body->content, body->read_size);
		ft_gnl_strlcat(body->content, buffer, (body->read_size + 1));
	}
	else
		ft_gnl_resize(body, buffer);
}

char	*get_next_line(int fd)
{
	static t_body	body = {0, 0, 0, 0, NULL, NULL};
	char			buffer[BUFFER_SIZE + 1];
	int				read_ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	body.fd = fd;
	read_ret = 0;
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	gnl_strlen(buffer, BUFFER_SIZE);
	if (ft_gnl_searcher(body.content) <= 0)
		read_ret = ft_gnl_read(&body, buffer);
	if (read_ret == 0)
	{
		ft_gnl_save_ret(&body);
		if (gnl_strlen(body.content, -1) == 0)
			ft_gnl_destroyer(&body.content);
	}
	else if (read_ret == -1)
		body.ret = ft_gnl_destroyer(&body.content);
	else if (read_ret == 1)
		body.ret = ft_gnl_destroyer(&body.content);
	return (body.ret);
}
