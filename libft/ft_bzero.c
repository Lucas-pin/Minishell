/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:34:32 by lpin              #+#    #+#             */
/*   Updated: 2023/09/22 17:30:22 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = 0;
		--n;
		s++;
	}
}

/*int	main(void)
{
	size_t	n;
	char	arr[5] = "aaa";
	char	arr_1[5] = "bbb";
	char	*pointer;
	char	*pointer_1;

	n = 1;
	pointer = arr;
	pointer_1 = arr_1;
	printf("Contenido previo de pointer %s\n", pointer);
	printf("Contenido previo pointer_1 %s\n", pointer_1);
	ft_bzero(pointer, n);
	bzero(pointer_1, n);
	printf("Contenido posterior pointer %s\n", pointer);
	printf("Contenido posterior pointer_1 %s\n", pointer_1);
}*/
