/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:11:04 by lpin              #+#    #+#             */
/*   Updated: 2023/10/12 13:41:25 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int	main(void)
{
	int	a;
	int	b;

	a = 128;
	b = 127;
	printf("isascii(%c) = %d\n", a, isascii(a));
	printf("ft_isasccii(%c) = %d\n", a, ft_isascii(a));
	printf("isascii(%c) = %d\n", b, isascii(b));
	printf("ft_isascii(%c) = %d\n", b, ft_isascii(b));
}*/
