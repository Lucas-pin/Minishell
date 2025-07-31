/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:00:03 by lpin              #+#    #+#             */
/*   Updated: 2023/10/12 13:41:31 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*int	main(void)
{
	char	a;
	char	b;

	a = 'a';
	b = '0';
	printf("isdigit(%c) = %d\n", a, isdigit(a));
	printf("ft_isdigit(%c) = %d\n", a, ft_isdigit(a));
	printf("isdigit(%c) = %d\n", b, isdigit(b));
	printf("ft_isdigit(%c) = %d\n", b, ft_isdigit(b));
}*/
