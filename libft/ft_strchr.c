/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 17:40:34 by lpin              #+#    #+#             */
/*   Updated: 2023/09/28 17:25:07 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s)
		++s;
	if (*s != (char)c)
		return (NULL);
	return ((char *)s);
}

/*int	main(void)
{
	char	str[] = "Argentina";
	int		c = 'l';

	printf("El puntero de str es: %s\n", ft_strchr(str, c));
	printf("El puntero de str es: %s\n", strchr(str, c));
	return (0);
}*/