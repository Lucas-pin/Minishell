/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:48:29 by lpin              #+#    #+#             */
/*   Updated: 2023/10/13 13:25:53 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memchr(const void *s, int c, size_t n)
{
	char	*temp;

	temp = NULL;
	while (n > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
		{
			temp = (char *)s;
			return (temp);
		}
		s++;
		--n;
	}
	return (temp);
}

/*int	main(void)
{
	char	arr[] = "bonjour";
	char	c = 'o';
    size_t  n = 7;
    char    *ft_prueba = ft_memchr(arr, c, n);
    char    *prueba = memchr(arr, c, n);
	printf("El puntero contiene: %s\n", ft_prueba);
	printf("El puntero contiene: %s\n", prueba);
	return (0);
}*/
