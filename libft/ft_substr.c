/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:13:12 by lpin              #+#    #+#             */
/*   Updated: 2023/10/31 13:49:06 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_errors(char const *s, unsigned int start, size_t len)
{
	if (!s)
		return (1);
	else if (start > ft_strlen(s) || len == 0)
		return (2);
	else if (((size_t)start + len) > ft_strlen(s))
		return (3);
	else
		return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		catch_error;

	ptr = NULL;
	catch_error = ft_check_errors(s, start, len);
	if (catch_error == 1)
		return (NULL);
	else if (catch_error == 2)
		return (ft_strdup(""));
	else if (catch_error == 3)
		len = ft_strlen(s) - (size_t)start;
	while (start > 0 && *s)
	{
		s++;
		--start;
	}
	ptr = ft_calloc((len + 1), sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

/*int	main(void)
{
	char	s1[] = "";
	char	*ft_ptr;

	ft_ptr = ft_substr(s1, 2, 5000000000);
	printf("ft_ptr contiene: %s\n", ft_ptr);
	printf("La longitud de ft_ptr es: %zu\n", ft_strlen(ft_ptr));
	return (0);
}*/
