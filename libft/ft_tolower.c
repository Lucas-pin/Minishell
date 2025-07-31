/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:42:39 by lpin              #+#    #+#             */
/*   Updated: 2023/09/23 21:47:32 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		return (c + 32);
	return (c);
}

/*int	main(void)
{
	char	c = '0';
	char	ft_c = '0';

	printf("El c es: %c\n", ft_tolower(c));
	printf("El ft_c es: %c\n", ft_tolower(ft_c));
	return (0);
}*/