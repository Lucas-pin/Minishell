/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manualva <manualva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:48:27 by manualva          #+#    #+#             */
/*   Updated: 2025/07/07 10:05:19 by manualva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	*substr_dup(const char *src, int start, int len)
{
	char	*out;
	int		i;

	out = malloc(len + 1);
	i = 0;
	if (!out)
		return (NULL);
	while (i < len)
	{
		out[i] = src[start + i];
		i++;
	}
	out[len] = '\0';
	return (out);
}
