/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:21:47 by lpin              #+#    #+#             */
/*   Updated: 2023/10/19 18:11:45 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_aux;
	char	*new;	
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s1);
	s1_aux = (char *)s1;
	if (*s1_aux == '\0')
		return (ft_strdup(""));
	while (ft_strchr(set, s1_aux[i]))
		++i;
	while (ft_strrchr(set, s1_aux[j]) && j > 0)
		--j;
	if (i > j || !s1 || !set)
		new = ft_calloc(1, sizeof(char));
	else
	{
		len = (j - i) + 1;
		new = ft_substr(s1_aux, (unsigned int)i, len);
	}
	return (new);
}

/*int	main(void)
{
	char	s1[] = "abcdba";
	char	s2[] = "acb";
	char	*ptr;

	ptr = ft_strtrim(s1, s2);
	printf("El puntero contiene: %s\n", ptr);
	printf("El puntero apunta a: %p\n", ptr);
	return (0);
}*/