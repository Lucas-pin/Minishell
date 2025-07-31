/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:40:50 by lpin              #+#    #+#             */
/*   Updated: 2024/09/09 18:28:25 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_gnl_searcher(const char *haystack)
{
	int		offset;
	char	*temp;

	offset = 0;
	temp = (char *)haystack;
	if (!haystack)
		return (-1);
	while (*temp && *temp != '\n')
	{
		++offset;
		temp++;
	}
	if (*temp == '\n')
		return (offset + 1);
	if (offset == 0)
		return (-1);
	else
		return (0);
}

char	*ft_gnl_put_forward(char *src, int len)
{
	int		i;
	char	*temp;

	i = gnl_strlen(src, -1);
	temp = src;
	if (!src || len == 0 || len == -1)
		return (src);
	while (i >= len)
	{
		*src = *(src + len);
		--i;
		src++;
	}
	while (*src)
	{
		*src = '\0';
		src++;
	}
	return (temp);
}

unsigned int	gnl_strlen(char *s, int i)
{
	unsigned int	len;

	len = 0;
	if (s == NULL || *s == '\0')
		return (0);
	if (i >= 0)
	{
		while (i >= 0)
		{
			s[i] = '\0';
			i--;
		}
		return (0);
	}
	else
	{
		while (s[len] != '\0')
			++len;
	}
	return (len);
}

unsigned int	ft_gnl_strlcat(char *dst, char *src, unsigned int dstsize)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	i;
	unsigned int	j;

	dst_len = gnl_strlen(dst, -1);
	src_len = gnl_strlen(src, -1);
	i = 0;
	j = 0;
	if (src == NULL || dstsize == 0)
		return (0);
	if (dstsize > 0 && dst_len < dstsize)
	{
		while (dst[i] != '\0')
			++i;
		while (src[j] != '\0' && j < (dstsize - dst_len - 1))
		{
			dst[i] = src[j];
			++i;
			++j;
		}
		dst[i] = '\0';
		return (dst_len + src_len);
	}
	return (src_len + dstsize);
}

void	*ft_gnl_destroyer(char **to_destroy)
{
	char	*temp;

	temp = *to_destroy;
	if (!temp)
		return (NULL);
	while (*temp)
	{
		*temp = '\0';
		temp++;
	}
	free(*to_destroy);
	*to_destroy = NULL;
	return (NULL);
}
