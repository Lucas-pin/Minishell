/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:48:30 by lpin              #+#    #+#             */
/*   Updated: 2023/10/12 13:41:17 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int	a;
	int	b;

	a = 'a';
	b = '0';
	printf("isalpha(%c) = %d\n", a, isalpha(a));
	printf("ft_isalpha(%c) = %d\n", a, ft_isalpha(a));
	printf("isalpha(%c) = %d\n", b, isalpha(b));
	printf("ft_isalpha(%c) = %d\n", b, ft_isalpha(b));
}*/
