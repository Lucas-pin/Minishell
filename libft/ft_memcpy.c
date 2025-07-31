/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:42:06 by lpin              #+#    #+#             */
/*   Updated: 2023/10/13 13:26:53 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*temp;

	temp = dst;
	if (!dst && !src)
		return (temp);
	while (n > 0)
	{
		*(char *)dst = *(char *)src;
		--n;
		dst++;
		src++;
	}
	return (temp);
}

/*int	main(void)
{
	size_t	n;
	char	src[] = "Argentina";
	char	src_1[] = "Argentina";
	char	dest[5] = "";
	char	dest_1[5] = "";
	char	*pointer;
	char	*pointer_1;

	n = 5;
	//printf("direccion dest = %p\n", dest);
	//printf("direccion dest_1 = %p\n", dest_1);
	pointer = ft_memcpy(src+3, src, n);
	pointer_1 = memcpy(src_1+3, src_1, n);
	//printf("Contenido pointer %s\n", pointer);
	//printf("Contenido pointer_1 %s\n", pointer_1);
	printf("Contenido src %s\n", src);
	printf("Contenido src_1 %s\n", src_1);
	//printf("Contenido dest_1 %s\n", dest_1);
	//printf("direccion ft_memcpy (pointer_2) = %p\n", pointer);
	//printf("direccion memcpy (pointer_3) = %p\n", pointer_1);
}*/