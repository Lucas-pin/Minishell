/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42malaga.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:10:47 by lucas             #+#    #+#             */
/*   Updated: 2025/07/05 13:47:47 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1_aux;
	unsigned char	*s2_aux;

	if (!s1 || !s2)
        return (-1);
    s1_aux = (unsigned char *)s1;
	s2_aux = (unsigned char *)s2;
	while (*s1_aux && *s2_aux)
	{
		if (*s1_aux != *s2_aux)
			return (*s1_aux - *s2_aux);
		s1_aux++;
		s2_aux++;
	}
    if (*s1_aux)
        return (*s1_aux);
	else if (*s2_aux)
		return (-*s2_aux);
	return (0);
}