/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:34:35 by lpin              #+#    #+#             */
/*   Updated: 2023/09/26 17:30:32 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	size;

	size = ft_strlen(s1) + 1;
	ptr = ft_calloc(size, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, size);
	return (ptr);
}

/*int	main(void)
{
	char	s1[] = "Argentina";
	char	*ft_ptr;
	char	*ptr;

	ft_ptr = ft_strdup(s1);
	ptr = strdup(s1);
	printf("ft_ptr contiene: %s\n", ft_ptr);
	printf("La longitud de ft_ptr es: %zu\n", ft_strlen(ft_ptr));
	printf("ptr contiene: %s\n", ptr);
	printf("La longitud de ptr es: %zu\n", ft_strlen(ptr));
	return (0);
}*/