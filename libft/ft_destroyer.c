/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroyer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:57:22 by lpin              #+#    #+#             */
/*   Updated: 2024/09/03 17:37:36 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_destroyer(char **to_destroy)
{
	char	*temp;

	temp = *to_destroy;
	if (!temp)
		return (NULL);
	while (*temp)
	{
		*temp = '\0';
		temp++;
	}
	free(*to_destroy);
	*to_destroy = NULL;
	return (NULL);
}
