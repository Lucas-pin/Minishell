/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:37:01 by lpin              #+#    #+#             */
/*   Updated: 2023/10/12 13:42:03 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}

/*int	main(void)
{
	char	c = '%';
	char	ft_c = '%';

	printf("El c es: %c\n", ft_toupper(c));
	printf("El ft_c es: %c\n", ft_toupper(ft_c));
	return (0);
}*/
