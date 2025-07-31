/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_s2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:01:23 by lpin              #+#    #+#             */
/*   Updated: 2024/09/03 17:40:29 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_s2(char const *s1, char *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	size_t	total_size;
	char	*ptr;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	total_size = size_s1 + size_s2 + 1;
	ptr = ft_calloc(total_size, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcat(ptr, s1, total_size);
	ft_strlcat(ptr, s2, total_size);
	free(s2);
	s2 = NULL;
	return (ptr);
}
