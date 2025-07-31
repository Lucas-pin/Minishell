/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:45:17 by lpin              #+#    #+#             */
/*   Updated: 2023/09/26 16:01:23 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (char *)malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

/*int	main(void)
{
	size_t	count;
	char	*ft_pointer;
	char	*pointer;

	count = 0;
	ft_pointer = ft_calloc(count, sizeof(char));
	ft_memset(ft_pointer, 42, (count * sizeof(char)));
	printf("ft_pointer contiene: %s\n", ft_pointer);
	printf("La longitud de ft_pointer es: %zu\n", ft_strlen(ft_pointer));
	printf("La dirr de ft_pointer es: %p\n", ft_pointer);
	pointer = calloc(count, sizeof(char));
	ft_memset(pointer, 42, (count * sizeof(char)));
	printf("pointer contiene: %s\n", pointer);
	printf("La longitud de pointer es: %zu\n", ft_strlen(pointer));
	printf("La dirr de pointer es: %p\n", pointer);
	return (0);
}*/