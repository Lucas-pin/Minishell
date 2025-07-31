/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_destroyer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:57:22 by lpin              #+#    #+#             */
/*   Updated: 2024/09/03 17:39:25 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_split_destroyer(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		ft_destroyer(split + i);
		i++;
	}
	free (split[i]);
	return (NULL);
}
