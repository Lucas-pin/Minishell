/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:49:15 by lpin              #+#    #+#             */
/*   Updated: 2024/09/04 20:54:17 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*temp;

	temp = b;
	if (!b)
		return (b);
	while (len > 0)
	{
		*(unsigned char *)b = (unsigned char) c;
		--len;
		b++;
	}
	return (temp);
}
/*
int	main(void)
{
	int		c;
	size_t	len;
	char	arr[10] = "bbbbbb";
	char	*pointer;
	char	*pointer_1;

	c = 65;
	len = 3;
	pointer = arr;
	pointer_1 = ft_memset(pointer, c, len);
	printf("retorno ft_memset (pointer) = %p\n", pointer);
	printf("retorno ft_memset (pointer_1) = %p\n", pointer_1);
	printf("Contenido pointer %s\n", pointer);
	pointer_1 = memset(pointer, c, len);
	printf("retorno memset (pointer_1) = %s\n", pointer);
	printf("retorno memset (pointer_1) = %p\n", pointer_1);
	printf("Contenido pointer %s\n", pointer);
}
*/
