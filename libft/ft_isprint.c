/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:18:51 by lpin              #+#    #+#             */
/*   Updated: 2023/10/12 13:41:34 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

/*int	main(void)
{
	int	a;
	int	b;

	a = 31;
	b = 32;
	printf("isprint(%c) = %d\n", a, isprint(a));
	printf("ft_isasccii(%c) = %d\n", a, ft_isprint(a));
	printf("isprint(%c) = %d\n", b, isprint(b));
	printf("ft_isprint(%c) = %d\n", b, ft_isprint(b));
}*/
