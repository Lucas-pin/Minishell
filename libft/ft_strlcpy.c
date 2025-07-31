/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:17:36 by lpin              #+#    #+#             */
/*   Updated: 2023/09/25 17:58:31 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	j = ft_strlen(src);
	if (dstsize == 0 || src == NULL)
		return (j);
	if (dstsize > 0)
	{
		while (src[i] != '\0' && (i < dstsize - 1))
		{
			dest[i] = src[i];
			++i;
		}
		dest[i] = '\0';
	}
	return (j);
}

/*int main()
{
	char	destiny_1[] = "hhhhhh";
	char	destiny[] = "hhhhhh";
    char	src_1[] = "abcssbbbb";
	size_t	size_1;
	size_t	size_2;
    
    size_1 = strlcpy(destiny_1, src_1, 5);
    size_2 = ft_strlcpy(destiny, src_1, 5);
    printf("El destino contiene: %s\n", destiny);
	printf("El destino_1 contiene: %s\n", destiny_1);
    return (0);
}*/