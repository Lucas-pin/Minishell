/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:12:52 by lpin              #+#    #+#             */
/*   Updated: 2023/10/12 18:10:40 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_aux;
	unsigned char	*s2_aux;

	s1_aux = (unsigned char *)s1;
	s2_aux = (unsigned char *)s2;
	while (n > 0 && *s1_aux && *s2_aux)
	{
		if (*s1_aux != *s2_aux)
			return (*s1_aux - *s2_aux);
		--n;
		s1_aux++;
		s2_aux++;
	}
	if (n != 0)
		return (*s1_aux - *s2_aux);
	return (0);
}

/*int	main(void)
{
	char	s1[] = "Ar";
	char	s2[] = "A";
	size_t n = 2;

	printf("ft_strncmp: %i\n", ft_strncmp(s1, s2, n));
	printf("strncmp: %i\n", strncmp(s1, s2, n));
	return (0);
}*/