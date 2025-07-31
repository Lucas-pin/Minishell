/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 23:14:00 by lpin              #+#    #+#             */
/*   Updated: 2023/09/24 23:17:53 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		--n;
		s1++;
		s2++;
	}
	return (0);
}

/*int	main(void)
{
	char	s1[] = "Arg\0e";
	char	s2[] = "Arg\0s";
	size_t n = 5;

	printf("ft_memcmp: %i\n", ft_memcmp(s1, s2, n));
	printf("memcmp: %i\n", memcmp(s1, s2, n));
	return (0);
}*/