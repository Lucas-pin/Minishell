/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:25:43 by lpin              #+#    #+#             */
/*   Updated: 2023/09/22 17:30:24 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*int	main(void)
{
	char	a;
	char	b;

	a = 'a';
	b = '%';
	printf("isalnum(%c) = %d\n", a, isalnum(a));
	printf("ft_isalnum(%c) = %d\n", a, ft_isalnum(a));
	printf("isalnum(%c) = %d\n", b, isalnum(b));
	printf("ft_isalnum(%c) = %d\n", b, ft_isalnum(b));
}*/
