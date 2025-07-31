/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:42:34 by lpin              #+#    #+#             */
/*   Updated: 2024/09/26 20:59:02 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

/*int	main(void)
{
	char	arr[6] = "Hello";

	printf("strlen(%s) = %lu\n", arr, strlen(arr));
	printf("ft_strlen(%s) = %lu\n", arr, ft_strlen(arr));
}*/